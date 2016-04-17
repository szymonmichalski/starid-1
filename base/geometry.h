#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <cassert>
#include <armadillo>
using namespace arma;

namespace base {

struct Pointing {
    Pointing();
    Pointing(double ra, double dec, double yaw);
    vec uv;
    double yaw;
    mat RotationMatrix();
    vec Quaternion();
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
