#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <cassert>
#include <armadillo>
using namespace arma;

namespace geometry {

constexpr double pi = datum::pi;
constexpr double RaOrion = 75.0*pi/180.0;
constexpr double DecOrion = 0.0*pi/180.0;
constexpr double RaCass = 0.0*pi/180.0;
constexpr double DecCass = 60.0*pi/180.0;

struct UnitVector {
    vec uv;
    UnitVector();
    UnitVector(double ra, double dec);
    double x();
    double y();
    double z();
};

struct RotationVector {
    vec rv;
    RotationVector();
};

struct RotationMatrix {
    mat rm;
    RotationMatrix();
    RotationMatrix(UnitVector& uv, double yaw);
};

struct Quaternion {
    vec q;
    Quaternion();
    Quaternion(UnitVector& uvec, double yaw);
    Quaternion(RotationMatrix& rm);
};

vec qmult(vec& q1, vec& q2);
vec qconj(vec& q);
vec rv2q(vec& rv);
vec q2rv(vec& q);
vec qdif2rv(vec& q1, vec& q2);
mat q2rm(vec& q);
vec rm2q(mat& rm);
double sgn(double x);
}
#endif
