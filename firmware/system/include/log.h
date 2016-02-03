#ifndef LOG_H
#define LOG_H

#ifdef __cplusplus

#include "ch.h"
#include "ff.h"
#include <string>


using namespace std;


#define LOG_PERIOD_MS   200


class Log {
    private:
                                            Log();
                                           ~Log();
    public:

        static void                         init();
        static FIL                          _file;
};

/*
 * #include <vector>
#include <initializer_list>
template< int elements, typename Type = double >
class Parameter {
    private:
                                            Parameter();
                                           ~Parameter();
    public:

        void                                update( std::initializer_list<Type> list );
    private:
        static RingBuffer< vector<Type> >          _settings;
};


template <typename Type = double>
using ScalarParameter = Parameter<1, Type>;

template <typename Type = double>
using VectorParameter = Parameter<3, Type>;
*/

#endif

#endif // LOG_H
