#ifndef GEOMETRY_VECTOR
#define GEOMETRY_VECTOR

#include "g_tensor.h"
#include "g_quaternion.h"

namespace geometry {

    template< int rows, int columns, typename Type >
    class Matrix;

#define VECTOR_BASE_FUNCTIONS(size) \
        Vector() {} \
        Vector( const Tensor<size, Type>& tensor ) : Tensor<size, Type>( tensor ) {} \
        Vector( std::initializer_list<Type> list ) : Tensor<size, Type>( list ) {} \
       ~Vector() {} \
 \
    template<typename otherType> \
    inline Vector<size, Type>&                  operator=( const Vector<size, otherType >& other ) { \
        for( int i=0; i<size; i++ ) \
            (*this)(i) = other(i); \
        return *this; \
    } \
    inline                                      operator Matrix<size, 1, Type>() { \
    Matrix<size, 1, Type> returnMatrix; \
        for( int i=0; i<size; i++ ) \
            returnMatrix(i,0) = (*this)(i); \
        return returnMatrix; \
    } \
 \
    inline                                      operator Matrix<size, 1, Type>() const { \
    Matrix<size, 1, Type> returnMatrix; \
        for( int i=0; i<size; i++ ) \
            returnMatrix(i,0) = (*this)(i); \
        return returnMatrix; \
    } \
 \
    inline \
    Type                                        norm() const { \
        Type norm = 0; \
        for( int i=0; i<size; i++ ) \
            norm += (*this)(i)*(*this)(i); \
        return sqrtf(norm); \
    } \
 \
    inline \
    void                                        normalize() { \
    Type norma; \
    norma = norm(); \
    if(norma) \
    for( int i=0; i<size; i++ ) \
        (*this)(i) /= norma;     \
    } \
 \
    inline \
    Vector<size, Type>                          normalized() { \
        Vector<size, Type> returnVector = *this; \
        returnVector.normalize(); \
        return returnVector; \
    } \


    template< int size, typename Type = DEFUALT_TYPE >
    class Vector : public Tensor<size, Type> {
        public:
            VECTOR_BASE_FUNCTIONS(size)
    };

    template< typename Type >
    class Vector<3, Type> : public Tensor<3, Type> {
        public:
            VECTOR_BASE_FUNCTIONS(3)

            Type&       x() {
                return (*this)(0);
            }
            const Type& x() const {
                return (*this)(0);
            }

            Type&       y() {
                return (*this)(1);
            }
            const Type& y() const {
                return (*this)(1);
            }

            Type&       z() {
                return (*this)(2);
            }
            const Type& z() const {
                return (*this)(2);
            }
    };


    template< int size, typename Type >
    std::ostream&                               operator<<( std::ostream& os, Vector<size, Type> instance ) {
        os << "Vector" << size << std::string( typeid(Type).name() ) << ":\n";
        for( int i=0; i<size; i++)
            os << instance(i) << "\n";
        return os;
    }

    template< int size, typename LeftType, typename RightType >
    typename std::common_type<LeftType, RightType>::type                    operator*( const Vector<size, LeftType>& left, const Vector<size, RightType>& right ) {
        typename std::common_type<LeftType, RightType>::type crossProduct = 0;
        for(int i = 0; i<size; i++) {
            crossProduct += left(i)*right(i);
        }
        return crossProduct;
    }

    template< int size, typename LeftType, typename RightType > \
    Vector< size, typename std::common_type<LeftType, RightType>::type >    operator+( const Vector<size, LeftType>& left, const Vector<size, RightType>& right ) { \
        Vector< size, typename std::common_type<LeftType, RightType>::type > returnVector;
        for(int i=0; i<size; i++)
            returnVector(i) = left(i) + right(i);
        return returnVector;
    }

    template< int size, typename LeftType, typename RightType > \
    Vector< size, typename std::common_type<LeftType, RightType>::type >    operator-( const Vector<size, LeftType>& left, const Vector<size, RightType>& right ) { \
        Vector< size, typename std::common_type<LeftType, RightType>::type > returnVector;
        for(int i=0; i<size; i++)
            returnVector(i) = left(i) - right(i);
        return returnVector;
    }

    template< typename LeftType, typename RightType >
    Vector< 3, typename std::common_type<LeftType, RightType>::type >       operator^( const Vector<3, LeftType>& left, const Vector<3, RightType>& right ) {
        Vector< 3, typename std::common_type<LeftType, RightType>::type > dotProduct;
        dotProduct.x() = left.y()*right.z() - left.z()*right.y();
        dotProduct.y() =-left.x()*right.z() + left.z()*right.x();
        dotProduct.z() = left.x()*right.y() - left.y()*right.x();
        return dotProduct;
    }

    template< int size, typename Type, typename Scalar >
    Vector<size, Type>                                               operator+( const Vector<size, Type>& left, const Scalar right ) {
        Vector<size, Type> returnVector;
        for(int i = 0; i<size; i++) {
            returnVector(i) = left(i) + right;
        }
        return returnVector;
    }
    template< int size, typename Type, typename Scalar >
    Vector<size, Type>                                               operator+( const Scalar left, const Vector<size, Type>& right ) {
        return right+left;
    }

    template< int size, typename Type, typename Scalar >
    Vector<size, Type>                                               operator-( const Vector<size, Type>& left, const Scalar right ) {
        Vector<size, Type> returnVector;
        for(int i = 0; i<size; i++) {
            returnVector(i) = left(i) - right;
        }
        return returnVector;
    }
    template< int size, typename Type, typename Scalar >
    Vector<size, Type>                                               operator-( const Scalar left, const Vector<size, Type>& right ) {
        return right-left;
    }

    template< int size, typename Type, typename Scalar >
    Vector<size, Type>                                               operator*( const Vector<size, Type>& left, const Scalar right ) {
        Vector<size, Type> returnVector;
        for(int i = 0; i<size; i++) {
            returnVector(i) = left(i) * right;
        }
        return returnVector;
    }
    template< int size, typename Type, typename Scalar >
    Vector<size, Type>                                               operator*( const Scalar left, const Vector<size, Type>& right ) {
        return right*left;
    }

    template< int size, typename Type, typename Scalar >
    Vector<size, Type>                                               operator/( const Vector<size, Type>& left, const Scalar right ) {
        Vector<size, Type> returnVector;
        for(int i = 0; i<size; i++) {
            returnVector(i) = left(i) / right;
        }
        return returnVector;
    }

}

#endif
