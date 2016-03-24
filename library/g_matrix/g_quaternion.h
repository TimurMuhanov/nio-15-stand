#ifndef GEOMETRY_QUATERNION
#define GEOMETRY_QUATERNION


#include "g_tensor.h"
#include "g_vector.h"
#include <math.h>


// form two vectors: (result quat should rotate one to another)
// transformation
// rotation angle
// rotation vector


namespace geometry {

    template< typename Type = DEFUALT_TYPE >
    class Quaternion {
        public:
            Quaternion() {
                _scalar = 1;
            }
            Quaternion( const Type scalar, const Vector<3, Type>& axis ) {
                _scalar = scalar;
                _vector = axis;
            }
            Quaternion(const Vector<4, Type>& vector ) {
                _scalar = vector(0);
                _vector = {vector(1), vector(2), vector(3)};
            }
            Quaternion( const Vector<3, Type>& originVector, const Vector<3, Type>& resultVector ) {
                ;
            }

            Quaternion( std::initializer_list<Type> list ) {
                int i=0;
                for( Type item : list )
                    if( i < 4 )
                        (*this)(i++) = item;
                for(; i<4; i++)
                    (*this)(i) = 0;
            }

           ~Quaternion() {}


            inline Type&       w() {
                return _scalar;
            }
            inline const Type& w() const {
                return _scalar;
            }

            inline Type&       x() {
                return _vector.x();
            }
            inline const Type& x() const {
                return _vector.x();
            }

            inline Type&       y() {
                return _vector.y();
            }
            inline const Type& y() const {
                return _vector.y();
            }

            inline Type&       z() {
                return _vector.z();
            }
            inline const Type& z() const {
                return _vector.z();
            }

            inline Type& scalar() {
                return _scalar;
            }
            inline const Type& scalar() const {
                return _scalar;
            }

            inline Vector<3, Type>& vector() {
                return _vector;
            }
            inline const Vector<3, Type>& vector() const {
                return _vector;
            }

            inline void angle(Type angle) {
                vector() = sin(angle/2)*axis();
                scalar() = cos(angle/2);
            }
            inline const Type angle() const {
                return acos(_scalar)*2;
            }

            inline void axis(const Vector<3, Type>& axis) {
                vector() = axis*sin(angle()/2);
            }
            inline const Vector<3, Type> axis() const {
                if( _scalar != 1 )
                    return _vector/(1-_scalar*_scalar);
                else
                    return Vector<3, Type>{0,0,0};
            }


            template<typename otherType>
            inline Quaternion<Type>&                    operator=( const Quaternion<otherType >& other ) {
                (*this).scalar() = other.scalar();
                (*this).vector() = other.vector();
                return *this;
            }

            inline Type&                                operator()( int index ) {
                if( index == 0 )
                    return _scalar;
                if( index>0 && index<4 )
                    return _vector(index-1);
            }

            inline const Type&                          operator()( int index ) const {
                if( index == 0 )
                    return _scalar;
                if( index>0 && index<4 )
                    return _vector(index-1);
            }

            inline
            Type                                        norm() const {
                return sqrt(  w()*w() + x()*x() + y()*y() + z()*z() );
            }

            inline
            void                                        normalize() {
                if(norm())
                (*this) = (*this)/norm();
            }

            inline
            Quaternion<Type>                            normalized() {
                Quaternion<Type> returnQuaternion = *this;
                returnQuaternion.normalize();
                return returnQuaternion;
            }

            inline
            void                                        conjugate() {
                this->vector() = -1*this->vector();
            }
            inline
            Quaternion<Type>                            conjugated() {
                return Quaternion<Type> (
                    this->scalar(),
                   -1*this->vector()
                );
            }

            inline                                      operator Vector<4, Type>() {
                Vector<4, Type> returnVector;
                returnVector(0) = w();
                returnVector(1) = x();
                returnVector(2) = y();
                returnVector(3) = z();
                return returnVector;
            }

        private:
            Type                _scalar;
            Vector<3,Type>      _vector;
    };

    template< typename Type >
    std::ostream&                        operator<<( std::ostream& os, Quaternion<Type> instance ) {
        os << "Quaternion" << std::string( typeid(Type).name() ) << "(" << instance.w() << ", " << instance.x() << ", " << instance.y() << ", " << instance.z() << ")\n";
        return os;
    }

    template< typename LeftType, typename RightType >
    Quaternion<typename std::common_type<LeftType, RightType>::type>    operator*( const Quaternion<LeftType>& left, const Quaternion<RightType>& right ) {
        return Quaternion<typename std::common_type<LeftType, RightType>::type> (
            left.scalar()*right.scalar() - left.vector()*right.vector(),
            (left.vector()^right.vector()) + left.scalar()*right.vector() + right.scalar()*left.vector()
        );
    }

    template< typename LeftType, typename RightType >
    Quaternion<typename std::common_type<LeftType, RightType>::type>    operator*( const Quaternion<LeftType>& left, const Vector<3, RightType>& right ) {
        return left*Quaternion<RightType>(0,right);
    }

    template< typename LeftType, typename RightType >
    Quaternion<typename std::common_type<LeftType, RightType>::type>    operator*( const Vector<3, RightType>& left, const Quaternion<LeftType>& right ) {
        return Quaternion<RightType>(0,left)*right;
    }

    template< typename LeftType, typename RightType >
    Quaternion<typename std::common_type<LeftType, RightType>::type>    operator+( const Quaternion<LeftType>& left, const Quaternion<RightType>& right ) {
        return Quaternion<typename std::common_type<LeftType, RightType>::type> (
            left.scalar() + right.scalar(),
            left.vector() + right.vector() );
    }

    template< typename LeftType, typename RightType >
    Quaternion<typename std::common_type<LeftType, RightType>::type>    operator-( const Quaternion<LeftType>& left, const Quaternion<RightType>& right ) {
        return Quaternion<typename std::common_type<LeftType, RightType>::type> (
            left.scalar() - right.scalar(),
            left.vector() - right.vector() );
    }


    template< typename Type, typename Scalar >
    Quaternion<Type>                                                    operator+( const Quaternion<Type>& left, const Scalar right ) {
        return Quaternion<Type> (
            left.scalar() + right,
            left.vector() + right );
    }
    template< typename Type, typename Scalar >
    Quaternion<Type>                                                    operator+( const Scalar left, const Quaternion<Type>& right ) {
        return right+left;
    }

    template< typename Type, typename Scalar >
    Quaternion<Type>                                                    operator-( const Quaternion<Type>& left, const Scalar right ) {
        return Quaternion<Type> (
            left.scalar() - right,
            left.vector() - right );
    }
    template< typename Type, typename Scalar >
    Quaternion<Type>                                                    operator-( const Scalar left, const Quaternion<Type>& right ) {
        return right-left;
    }

    template< typename Type, typename Scalar >
    Quaternion<Type>                                                    operator*( const Quaternion<Type>& left, const Scalar right ) {
        return Quaternion<Type> (
            left.scalar()*right,
            left.vector()*right );
    }
    template< typename Type, typename Scalar >
    Quaternion<Type>                                                    operator*( const Scalar left, const Quaternion<Type>& right ) {
        return right*left;
    }

    template< typename Type, typename Scalar >
    Quaternion<Type>                                                    operator/( const Quaternion<Type>& left, const Scalar right ) {
        return Quaternion<Type> (
            left.scalar()/right,
            left.vector()/right );
    }

}

#endif
