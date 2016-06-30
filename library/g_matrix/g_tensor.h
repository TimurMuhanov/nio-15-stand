#ifndef GEOMETRY_TENSOR
#define GEOMETRY_TENSOR

#include <typeinfo>
#include <initializer_list>
#include <string>
#include <iostream>
//#include <QDebug>
//#include <QString>


#define DEFUALT_TYPE        float


namespace geometry {

    template< int elements, typename Type = DEFUALT_TYPE >
    class Tensor {
        public:
                                                    Tensor() {
                for(int i=0; i<elements; i++)
                    array[i] = 0;
            }

                                                    Tensor( const Tensor<elements, Type>& other ) {
                for(int i=0; i<elements; i++)
                    array[i] = other.array[i];
            }

                                                    Tensor( std::initializer_list<Type> list ) {
                int i=0;
                for( Type item : list )
                    if( i < elements )
                        array[i++] = item;
                for(; i<elements; i++)
                    array[i] = 0;
            }

                                                   ~Tensor() {}

            inline Type&                            operator()( int index ) {
                if( index < elements )
                    return Tensor<elements, Type>::array[ index ];
            }

            inline const Type&                      operator()( int index ) const {
                if( index < elements )
                    return Tensor<elements, Type>::array[ index ];
            }

            template<typename otherType>
            inline                                       operator Tensor<elements, otherType>() {
                Tensor<elements, otherType> returnTensor;
                for( int i=0; i<elements; i++ )
                    returnTensor(i) = (*this)(i);
                return returnTensor;
            }

            template<typename otherType>
            inline                                       operator Tensor<elements, otherType>() const {
                Tensor<elements, otherType> returnTensor;
                for( int i=0; i<elements; i++ )
                    returnTensor(i) = (*this)(i);
                return returnTensor;
            }

        protected:
            Type                                    array[elements];
    };

}

#endif
