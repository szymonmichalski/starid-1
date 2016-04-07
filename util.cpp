#include "util.h"
using namespace arma;

util::UnitVector::UnitVector(double ra, double dec) {
    v = { cos(ra)*cos(dec), sin(ra)*cos(dec), sin(dec) };
    v = normalise(v);
    assert(norm(v) - 1.0 < 1e-10);
}
double util::UnitVector::UnitVector::x() {return v(0);}
double util::UnitVector::UnitVector::y() {return v(1);}
double util::UnitVector::UnitVector::z() {return v(2);}

util::RotationMatrix::RotationMatrix(UnitVector &v, double yaw) {
    vec bz { v.v(0), v.v(1), v.v(2) };
    vec iz { 0.0, 0.0, 1.0 };
    vec b1x { cross(bz,iz) };
    vec b1y { cross(bz,b1x) };
    vec bx { cos(yaw)*b1x + sin(yaw)*b1y };
    vec by { sin(yaw)*b1x + cos(yaw)*b1y };
    m.col(1) = bx;
    m.col(2) = by;
    m.col(3) = bz;
    assert (norm(m) - 1.0 <= 1e-10);
}

util::Quaternion::Quaternion(UnitVector &uvec, double yaw) {
    RotationMatrix m(uvec, yaw);
    q = m2q(m.m);
    assert (norm(q) - 1.0 <= 1e-10);
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

vec util::r2q(vec &r) {
    vec q { r(0)/2, r(1)/2, r(2)/2, 1 };
    q = normalise(q);
    if (q(3) < 0.0) q = -q;
    return q;
}

vec util::q2r(vec &q) {
    vec r { 2*q(0), 2*q(1), 2*q(2) };
    return r;
}

vec util::qdif2r(vec &q1, vec &q2a) {
    vec q2 { -q2a(0), -q2a(1), -q2a(2), q2a(3) };
    vec q3 {
            q1(0)*q2(3) + q1(1)*q2(2) + -q1(2)*q2(1) + q1(3)*q2(0),
            -q1(0)*q2(2) + q1(1)*q2(3) + q1(2)*q2(0) + q1(3)*q2(1),
            q1(0)*q2(1) + -q1(1)*q2(0) + q1(2)*q2(3) + q1(3)*q2(2),
            -q1(0)*q2(0) + -q1(1)*q2(1) + -q1(2)*q2(2) + q1(3)*q2(3)
    };
    q3 = normalise(q3);
    if ( q3(3) < 0 ) { q3 = -q3; }
    vec r { 2.0*q3(0), 2.0*q3(1), 2.0*q3(2) };
    return r;
}

mat util::q2m(vec &q) {
    mat m(3,3);
    m(0,0) =  q(0)*q(0) - q(1)*q(1) - q(2)*q(2) + q(3)*q(3);
    m(0,1) = 2.0*( q(0)*q(1) + q(2)*q(3) );
    m(0,2) = 2.0*( q(0)*q(2) - q(1)*q(3) );
    m(1,0) = 2.0*( q(0)*q(1) - q(2)*q(3) );
    m(1,1) = -q(0)*q(0) + q(1)*q(1) - q(2)*q(2) + q(3)*q(3);
    m(1,2) = 2.0*( q(1)*q(2) + q(0)*q(3) );
    m(2,0) = 2.0*( q(0)*q(2) + q(1)*q(3) );
    m(2,1) = 2.0*( q(1)*q(2) - q(0)*q(3) );
    m(2,2) = -q(0)*q(0) - q(1)*q(1) + q(2)*q(2) + q(3)*q(3);
    return m;
}

vec util::m2q(mat &m) {
    vec q { 0.0, 0.0, 0.0, 1.0 };
    q(0) = 0.5 * sqrt(1.0 + m(0,0) - m(1,1) - m(2,2)) * sgn( m(1,2)-m(2,1) );
    q(1) = 0.5 * sqrt(1.0 - m(0,0) + m(1,1) - m(2,2)) * sgn( m(2,0)-m(0,2) );
    q(2) = 0.5 * sqrt(1.0 - m(0,0) - m(1,1) + m(2,2)) * sgn( m(0,1)-m(1,0) );
    q(3) = 0.5 * sqrt(1.0 + m(0,0) + m(1,1) + m(2,2));
    q = normalise(q);
    if (q(3) < 0.0) q = -q;
    return q;
}

double util::sgn(double x) { // nonstandard signum return +1 for 0
  if (x >= 0.0) return 1.0;
  if (x < 0.0) return -1.0;
  return 1.0;
}
