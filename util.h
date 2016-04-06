#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <cassert>
#include <armadillo>
using namespace arma;

namespace util {

    constexpr double pi = datum::pi;
    constexpr double UnixTimeToJ2000Offset = 946684800.0;
    constexpr double RaOrion = 75.0*pi/180.0;
    constexpr double DecOrion = 0.0*pi/180.0;
    constexpr double RaCass = 0.0*pi/180.0;
    constexpr double DecCass = 60.0*pi/180.0;

    struct UnitVector {
        UnitVector(double ra=0.0, double dec=0.0);
        vec v { 1.0, 0.0, 0.0 };
        void Xyz(double x=1.0, double y=0.0, double z=0.0);
        double Angle(UnitVector uvec2);
        double x {0.0};
        double y {0.0};
        double z {0.0};
    };
    struct RotationMatrix {
        RotationMatrix(UnitVector &uvec, double yaw=0.0); // yaw radians
        mat m { mat(3,3,fill::eye) };
    };
    struct Quaternion {
        Quaternion(UnitVector &uvec, double yaw=0.0); // yaw radians
        vec q { 0.0, 0.0, 0.0, 1.0 };
    };

    vec qmult(vec &q1, vec &q2);
    vec qconj(vec &q);
    vec r2q(vec &r);
    vec q2r(vec &q);
    vec qdif2r(vec &q1, vec &q2);
    mat q2m(vec &q);
    vec m2q(mat &m);
    double sgn(double x);
}
#endif
