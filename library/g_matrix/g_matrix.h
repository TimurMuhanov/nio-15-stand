#ifndef GEOMETRY_MATRIX
#define GEOMETRY_MATRIX


#include "g_tensor.h"
#include <functional>


namespace geometry {
    template< int size, typename Type >
    class Vector;

    template< typename Type >
    class Quaternion;

#define MATRIX_BASE_FUNCTIONS(rows, columns)        \
        Matrix() {} \
        Matrix( std::initializer_list<Type> list ) : Tensor<rows*columns, Type>( list ) {} \
       ~Matrix() {} \
 \
    template<typename otherType> \
    inline Matrix<rows, columns, Type>&     operator=( const Matrix<rows, columns, otherType >& other ) { \
        for( int i=0; i<rows*columns; i++ ) \
            Tensor<rows*columns, Type>::array[i] = other.array[i]; \
        return *this; \
    } \
 \
    inline Type&                                operator()( int row, int column ) { \
        if( row < rows && column < columns ) \
            return Tensor<rows*columns, Type>::array[ row*columns+column ]; \
    } \
 \
    inline const Type&                          operator()( int row, int column ) const { \
        if( row < rows && column < columns ) \
            return Tensor<rows*columns, Type>::array[ row*columns+column ]; \
    }



    template< int rows, int columns, typename Type = DEFUALT_TYPE >
    class Matrix : public Tensor<rows*columns, Type> {
        public:
            MATRIX_BASE_FUNCTIONS(rows, columns)

            inline Matrix<columns, rows, Type>             transponced() {
                Matrix<columns, rows, Type> returnMatrix;
                for( int i=0; i<rows; i++) {
                    for( int j=0; j<columns; j++)
                        returnMatrix(j,i) = (*this)(i,j);
                }
                return returnMatrix;
            }
    };

    template< typename Type >
    class Matrix<4, 1, Type> : public Tensor<4, Type> {
        public:
            MATRIX_BASE_FUNCTIONS(4, 1)

            inline                                      operator Quaternion<Type>() {
                Quaternion<Type> returnQuaternion;
                for( int i=0; i<4; i++ )
                    returnQuaternion(i) = (*this)(i,0);
                return returnQuaternion;
            }
    };

    template< int size, typename Type >
    class Matrix<size, 1, Type> : public Tensor<size, Type> {
        public:
            MATRIX_BASE_FUNCTIONS(size, 1)

            inline                                      operator Vector<size, Type>() {
                Vector<size, Type> returnVector;
                for( int i=0; i<size; i++ )
                    returnVector(i) = (*this)(i,0);
                return returnVector;
            }
    };

    template< int size, typename Type >
    class Matrix<size, size, Type> : public Tensor<size*size, Type> {
        public:
            MATRIX_BASE_FUNCTIONS(size, size)

            inline Type                                 determinant() {
                Type returnValue=1;
                Matrix< size, size, Type > L;
                Matrix< size, size, Type > U;
                decompose( L, U );
                for(int i=0; i<size; i++) {
                    returnValue *= L(i,i)*U(i,i);
                }
                return returnValue;
            }

            inline Matrix<size, size, Type>             inversed() {
                Matrix<size, size, Type> B;
                Matrix<size, size, Type> A = *this;
                double temp;
                for( int i = 0; i < size; i++ )
                    for( int j = 0; j < size; j++ )
                        if( i == j )
                            B(i,j) = 1.0;

                for( int k = 0; k < size; k++ ) {
                    temp = A(k,k);

                    for( int j = 0; j < size; j++ ) {
                        A(k,j) /= temp;
                        B(k,j) /= temp;
                    }

                    for( int i = k + 1; i < size; i++ ) {
                        temp = A(i,k);

                        for( int j = 0; j < size; j++ ) {
                            A(i, j) -= A(k, j) * temp;
                            B(i, j) -= B(k, j) * temp;
                        }
                    }
                }

                for( int k = size - 1; k > 0; k-- ) {
                    for( int i = k - 1; i >= 0; i-- ) {
                        temp = A(i, k);

                        for( int j = 0; j < size; j++ ) {
                            A(i, j) -= A(k, j) * temp;
                            B(i, j) -= B(k, j) * temp;
                        }
                    }
                }

                return B;
            }

            inline void                                 decompose( Matrix< size, size, Type >& L, Matrix< size, size, Type >& U ) {
                for( int i = 0; i < size; i++ ) {
                    for( int j = 0; j < size; j++ ) {
                        if( j < i )
                            L(j, i) = 0;
                        else {
                            L(j, i) = (*this)(j, i);
                            for( int k = 0; k < i; k++ ) {
                                L(j, i) = L(j, i) - L(j, k) * U(k, i);
                            }
                        }
                    }
                    for( int j = 0; j < size; j++ ) {
                        if( j < i )
                            U(i, j) = 0;
                        else if( j == i )
                            U(i, j) = 1;
                        else {
                            U(i, j) = (*this)(i, j) / L(i, i);
                            for( int k = 0; k < i; k++ ) {
                                U(i, j) = U(i, j) - ( ( L(i, k) * U(k, j) ) / L(i, i) );
                            }
                        }
                    }
                }
            }
    };


    template< int rows, int columns, typename Type >
    std::ostream& operator<<(std::ostream& os, Matrix<rows, columns, Type> instance) {
        os << "Matrix" << rows << "x" << columns << std::string( typeid(Type).name() ) << ":\n";
        for( int i=0; i<rows; i++) {
            for( int j=0; j<columns; j++)
                os << instance(i, j) << " ";
            os << "\n";
        }
        return os;
    }

    template< int leftRows, int common, int rightColumns, typename LeftType, typename RightType >
    Matrix< leftRows, rightColumns, typename std::common_type<LeftType, RightType>::type >  operator*( const Matrix< leftRows, common, LeftType >& left, const Matrix< common, rightColumns, RightType >& right ) {
        Matrix< leftRows, rightColumns, typename std::common_type<LeftType, RightType>::type > returnMatrix;
        for(int i=0; i<leftRows; i++)
           for(int j=0; j<rightColumns; j++) {
               returnMatrix(i,j) = 0;
               for(int k=0; k<common; k++)
                   returnMatrix(i,j) += left(i,k)*right(k,j);
           }
        return returnMatrix;
    }

    template< int rows, int columns, typename LeftType, typename RightType >
    Matrix< rows, 1, typename std::common_type<LeftType, RightType>::type >         operator*( const Matrix< rows, columns, LeftType >& left, const Vector< columns, RightType >& right ) {
        return left*(Matrix<columns, 1, RightType>)right;
    }

    template< int size, int columns, typename LeftType, typename RightType >
    Matrix< size, columns, typename std::common_type<LeftType, RightType>::type >   operator*( const Vector< size, LeftType >& left, const Matrix< 1, columns, RightType >& right ) {
        return (Matrix<size, 1, LeftType>)left*right;
    }

    template< int rows, int columns, typename LeftType, typename RightType >
    Matrix< rows, columns, typename std::common_type<LeftType, RightType>::type >   operator+( const Matrix<rows, columns, LeftType>& left, const Matrix<rows, columns, RightType>& right ) { \
        Matrix< rows, columns, typename std::common_type<LeftType, RightType>::type > returnMatrix;
        for(int i=0; i<rows; i++)
            for(int j=0; j<columns; j++) {
                returnMatrix(i,j) = left(i,j) + right(i,j);
        }
        return returnMatrix;
    }

    template< int rows, int columns, typename LeftType, typename RightType > \
    Matrix< rows, columns, typename std::common_type<LeftType, RightType>::type >   operator-( const Matrix<rows, columns, LeftType>& left, const Matrix<rows, columns, RightType>& right ) { \
        Matrix< rows, columns, typename std::common_type<LeftType, RightType>::type > returnMatrix;
        for(int i=0; i<rows; i++)
            for(int j=0; j<columns; j++) {
                returnMatrix(i,j) = left(i,j) - right(i,j);
        }
        return returnMatrix;
    }

    template< int rows, int columns, typename Type, typename Scalar >
    Matrix< rows, columns, Type>                                     operator+( const Matrix< rows, columns, Type>& left, const Scalar right ) {
        Matrix< rows, columns, Type> returnMatrix;
        for(int i=0; i<rows; i++)
            for(int j=0; j<columns; j++)
                returnMatrix(i,j) = left(i,j) + right;
        return returnMatrix;
    }
    template< int rows, int columns, typename Type, typename Scalar >
    Matrix< rows, columns, Type>                                     operator+( const Scalar left, const Matrix< rows, columns, Type>& right ) {
        return right+left;
    }


    template< int rows, int columns, typename Type, typename Scalar >
    Matrix< rows, columns, Type>                                     operator-( const Matrix< rows, columns, Type>& left, const Scalar right ) {
        Matrix< rows, columns, Type> returnMatrix;
        for(int i=0; i<rows; i++)
            for(int j=0; j<columns; j++)
                returnMatrix(i,j) = left(i,j) - right;
        return returnMatrix;
    }
    template< int rows, int columns, typename Type, typename Scalar >
    Matrix< rows, columns, Type>                                     operator-( const Scalar left, const Matrix< rows, columns, Type>& right ) {
        return right-left;
    }

    template< int rows, int columns, typename Type, typename Scalar >
    Matrix< rows, columns, Type>                                     operator*( const Matrix< rows, columns, Type>& left, const Scalar right ) {
        Matrix< rows, columns, Type> returnMatrix;
        for(int i=0; i<rows; i++)
            for(int j=0; j<columns; j++)
                returnMatrix(i,j) = left(i,j) * right;
        return returnMatrix;
    }
    template< int rows, int columns, typename Type, typename Scalar >
    Matrix< rows, columns, Type>                                     operator*( const Scalar left, const Matrix< rows, columns, Type>& right ) {
        return right*left;
    }

    template< int rows, int columns, typename Type, typename Scalar >
    Matrix< rows, columns, Type>                                     operator/( const Matrix< rows, columns, Type>& left, const Scalar right ) {
        Matrix< rows, columns, Type> returnMatrix;
        for(int i=0; i<rows; i++)
            for(int j=0; j<columns; j++)
                returnMatrix(i,j) = left(i,j) / right;
        return returnMatrix;
    }

    template<int rows, int columns, typename Type>
    Matrix< rows, columns, Type >                                  jacobian( const std::function< Vector<rows, Type>( Vector<columns, Type>) > function, const Vector<columns, Type> point ) {
        Type step = 1e-5;
        Matrix< rows, columns, Type> returnMatrix;
        for( int i = 0; i < rows; i++ ) {
            Type current = function(point)(i);
            for( int j = 0; j < columns; j++ ) {
                Vector<columns, Type> unit;
                unit(j)=1;
                returnMatrix(i, j) =  ( function(point + step*unit )(i) - current )/step;
            }
        }

        return returnMatrix;
    }

}


#endif
