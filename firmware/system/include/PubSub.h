#ifndef PUBSUB_H
#define PUBSUB_H


#include "ch.hpp"
#include "g_matrix.h"
#include "g_vector.h"
#include "g_quaternion.h"

#include <queue>

using namespace geometry;
using namespace std;
using namespace chibios_rt;


typedef struct {
    Vector<3>   val;
    u32         time;			// us
} vectorData;

typedef struct {
    float       val;
    u32         time;			// us
} scalarData;

typedef struct {
    Quaternion<>    val;
    u32             time;       // us
} quaternionData;


template< typename Type >
class Topic {
    public:
                                        Topic() {}
                                       ~Topic() {}


                                        operator Type() {
            _mutex.lock();
            Type tmp = _data;
            _mutex.unlock();
            return tmp;
        }

        Type                            get() {
            _sem.wait();
            return (Type)(*this);
        }

        void                            operator=( const Type& value ) {
            put(value);
        }

        void                            put( const Type& value ) {
            _mutex.lock();
            _data = value;
            _mutex.unlock();
            _sem.signal();
        }

    private:
        Type                            _data;
        Mutex                           _mutex;
        BinarySemaphore                 _sem{true};
};



//class Topics {
//    public:
////        static Topic<vectorData>        accelRaw;
//        static Topic<vectorData>        accel;

//        static Topic<vectorData>        gyroRaw;
//        static Topic<vectorData>        gyro;

//        static Topic<vectorData>        magRaw;
//        static Topic<vectorData>        mag;

//        static Topic<scalarData>        temp;
//        static Topic<scalarData>        press;

//        static Topic<quaternionData>    quat;
//};

#endif
