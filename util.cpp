#include "util.h"
using namespace arma;

util::UnitVector::UnitVector(double ra, double dec) {
    uv = { cos(ra)*cos(dec), sin(ra)*cos(dec), sin(dec) };
    uv = normalise(uv);
    assert(norm(uv) - 1.0 < 1e-10);
}
double util::UnitVector::UnitVector::x() {return uv(0);}
double util::UnitVector::UnitVector::y() {return uv(1);}
double util::UnitVector::UnitVector::z() {return uv(2);}

util::RotationMatrix::RotationMatrix(UnitVector &uvec, double yaw) {
    vec bz { uvec.uv(0), uvec.uv(1), uvec.uv(2) };
    vec iz { 0.0, 0.0, 1.0 };
    vec b1x { cross(bz,iz) };
    vec b1y { cross(bz,b1x) };
    vec bx { cos(yaw)*b1x + sin(yaw)*b1y };
    vec by { sin(yaw)*b1x + cos(yaw)*b1y };
    rm.col(0) = bx;
    rm.col(1) = by;
    rm.col(2) = bz;
}

util::Quaternion::Quaternion(UnitVector &uvec, double yaw) {
    RotationMatrix rm(uvec, yaw);
    q = rm2q(rm.rm);
}

vec util::qmult(vec &q1, vec &q2) {
    vec q3 {
            q1(0)*q2(3) + q1(1)*q2(2) + -q1(2)*q2(1) + q1(3)*q2(0),
            -q1(0)*q2(2) + q1(1)*q2(3) + q1(2)*q2(0) + q1(3)*q2(1),
            q1(0)*q2(1) + -q1(1)*q2(0) + q1(2)*q2(3) + q1(3)*q2(2),
            -q1(0)*q2(0) + -q1(1)*q2(1) + -q1(2)*q2(2) + q1(3)*q2(3)
    };
    q3 = normalise(q3);
    if (q3(3) < 0.0) q3 = -q3;
    return q3;
}

vec util::qconj(vec &q) {
    vec q2 { -q(0), -q(1), -q(2), q(3) };
    return q2;
}

vec util::rv2q(vec &rv) {
    vec q { rv(0)/2, rv(1)/2, rv(2)/2, 1 };
    q = normalise(q);
    if (q(3) < 0.0) q = -q;
    return q;
}

vec util::q2rv(vec &q) {
    vec rv { 2*q(0), 2*q(1), 2*q(2) };
    return rv;
}

vec util::qdif2rv(vec &q1, vec &q2a) {
    vec q2 { -q2a(0), -q2a(1), -q2a(2), q2a(3) };
    vec q3 {
            q1(0)*q2(3) + q1(1)*q2(2) + -q1(2)*q2(1) + q1(3)*q2(0),
            -q1(0)*q2(2) + q1(1)*q2(3) + q1(2)*q2(0) + q1(3)*q2(1),
            q1(0)*q2(1) + -q1(1)*q2(0) + q1(2)*q2(3) + q1(3)*q2(2),
            -q1(0)*q2(0) + -q1(1)*q2(1) + -q1(2)*q2(2) + q1(3)*q2(3)
    };
    q3 = normalise(q3);
    if ( q3(3) < 0 ) { q3 = -q3; }
    vec rv { 2.0*q3(0), 2.0*q3(1), 2.0*q3(2) };
    return rv;
}

mat util::q2rm(vec &q) {
    mat rm(3,3);
    rm(0,0) =  q(0)*q(0) - q(1)*q(1) - q(2)*q(2) + q(3)*q(3);
    rm(0,1) = 2.0*( q(0)*q(1) + q(2)*q(3) );
    rm(0,2) = 2.0*( q(0)*q(2) - q(1)*q(3) );
    rm(1,0) = 2.0*( q(0)*q(1) - q(2)*q(3) );
    rm(1,1) = -q(0)*q(0) + q(1)*q(1) - q(2)*q(2) + q(3)*q(3);
    rm(1,2) = 2.0*( q(1)*q(2) + q(0)*q(3) );
    rm(2,0) = 2.0*( q(0)*q(2) + q(1)*q(3) );
    rm(2,1) = 2.0*( q(1)*q(2) - q(0)*q(3) );
    rm(2,2) = -q(0)*q(0) - q(1)*q(1) + q(2)*q(2) + q(3)*q(3);
    return rm;
}

vec util::rm2q(mat &rm) {
    vec q { 0.0, 0.0, 0.0, 1.0 };
    q(0) = 0.5 * sqrt(1.0 + rm(0,0) - rm(1,1) - rm(2,2)) * sgn( rm(1,2)-rm(2,1) );
    q(1) = 0.5 * sqrt(1.0 - rm(0,0) + rm(1,1) - rm(2,2)) * sgn( rm(2,0)-rm(0,2) );
    q(2) = 0.5 * sqrt(1.0 - rm(0,0) - rm(1,1) + rm(2,2)) * sgn( rm(0,1)-rm(1,0) );
    q(3) = 0.5 * sqrt(1.0 + rm(0,0) + rm(1,1) + rm(2,2));
    q = normalise(q);
    if (q(3) < 0.0) q = -q;
    return q;
}

double util::sgn(double x) { // nonstandard signum return +1 for 0
  if (x >= 0.0) return 1.0;
  if (x < 0.0) return -1.0;
  return 1.0;
}
