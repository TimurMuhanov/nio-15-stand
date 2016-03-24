#include <QCoreApplication>
#include <QMatrix>
#include "matrix.h"
#include "vector.h"
#include "quaternion.h"

using namespace geometry;

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Vector<3> v1;
    Vector<3> v2 = 5*v1;
    v2 = v1+4;
    std::cout << v1 << v1+5 << 10*(v1+5)<<v2(0)<<v2(1)<<v2(2);

    Matrix<3,3> m1;
    Matrix<3,3> m2 = 5*m1;
    m2 = m1+4;
    std::cout << m1 << m1+5 << 10*(m1+5);

    Vector<3,float> y1 {1,2,3};
    Vector<3,int> y2;

    Matrix<3,1> mv = v1;

    y2 = y1;

    Quaternion<> q1{.5,1,2,3};
    //Quaternion<> q2;
    std::cout << q1 << q1.conjugated()<< q1.y() << q1.normalized() << q1.vector();
    q1.normalize();
    std::cout << q1;
    Matrix<4,6> m5;
    m5(0,0) = 1;
    m5(0,1) = 2;
    m5(1,0) = 3;
    std::cout << m5;

    Vector<3,float> f{1,0,0},r;
    Quaternion<float> temp{0.707,0,0.707,0};
    temp.normalize();
    r=(temp*f*temp.conjugated()).vector();
    std::cout <<r;
    return a.exec();
}

