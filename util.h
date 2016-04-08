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
        vec uv { 1.0, 0.0, 0.0 };
        UnitVector(double ra=0.0, double dec=0.0);
        double x();
        double y();
        double z();
    };

    struct RotationVector {
        vec rv { 0.0, 0.0, 0.0 };
    };

    struct RotationMatrix {
        mat rm { mat(3,3,fill::eye) };
        RotationMatrix(UnitVector &uvec, double yaw=0.0); // yaw radians
    };

    struct Quaternion {
        vec q { 0.0, 0.0, 0.0, 1.0 };
        Quaternion(UnitVector &uvec, double yaw=0.0); // yaw radians
    };

    vec qmult(vec &q1, vec &q2);
    vec qconj(vec &q);
    vec rv2q(vec &rv);
    vec q2rv(vec &q);
    vec qdif2rv(vec &q1, vec &q2);
    mat q2rm(vec &q);
    vec rm2q(mat &rm);
    double sgn(double x);
}
#endif
