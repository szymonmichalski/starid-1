#include "pointing.h"

#include <string>
#include <iostream>
#include <cmath>
#include <cassert>

base::Pointing::Pointing() {}
base::Pointing::Pointing(double ra=0.0, double dec=0.0, double yaw=0.0) : yaw(yaw) {
    uv.set_size(3);
    uv(0) = cos(ra)*cos(dec);
    uv(1) = sin(ra)*cos(dec);
    uv(2) = sin(dec);
    uv = normalise(uv);
    assert(norm(uv) == 1.0);
}

arma::mat base::Pointing::RotationMatrix() {
    arma::mat rm;
    rm.set_size(3,3);
    arma::vec bz = uv;
    arma::vec iz = { 0.0, 0.0, 1.0 };
    arma::vec b1x = cross(bz,iz);
    b1x = normalise(b1x);
    arma::vec b1y = cross(bz,b1x);
    b1y = normalise(b1y);
    arma::vec bx = cos(yaw)*b1x + sin(yaw)*b1y;
    arma::vec by = sin(yaw)*b1x + cos(yaw)*b1y;
    rm.col(0) = bx;
    rm.col(1) = by;
    rm.col(2) = bz;
    assert(det(rm) == 1.0);
    return rm;
}

arma::vec base::Pointing::Quaternion() {
    arma::mat rm = RotationMatrix();
    arma::vec q;
    q.set_size(4);
    q = rm2q(rm);
    q = normalise(q);
    assert(norm(q) == 1.0);
    return q;
}

arma::vec base::qmult(arma::vec& q1, arma::vec& q2) {
    arma::vec q3 {
        q1(0)*q2(3) + q1(1)*q2(2) + -q1(2)*q2(1) + q1(3)*q2(0),
                -q1(0)*q2(2) + q1(1)*q2(3) + q1(2)*q2(0) + q1(3)*q2(1),
                q1(0)*q2(1) + -q1(1)*q2(0) + q1(2)*q2(3) + q1(3)*q2(2),
                -q1(0)*q2(0) + -q1(1)*q2(1) + -q1(2)*q2(2) + q1(3)*q2(3)
    };
    q3 = normalise(q3);
    if (q3(3) < 0.0) q3 = -q3;
    return q3;
}

arma::vec base::qconj(arma::vec& q) {
    arma::vec q2 { -q(0), -q(1), -q(2), q(3) };
    return q2;
}

arma::vec base::rv2q(arma::vec& rv) {
    arma::vec q { rv(0)/2, rv(1)/2, rv(2)/2, 1 };
    q = normalise(q);
    if (q(3) < 0.0) q = -q;
    return q;
}

arma::vec base::q2rv(arma::vec& q) {
    arma::vec rv { 2*q(0), 2*q(1), 2*q(2) };
    return rv;
}

arma::vec base::qdif2rv(arma::vec& q1, arma::vec& q2a) {
    arma::vec q2 { -q2a(0), -q2a(1), -q2a(2), q2a(3) };
    arma::vec q3 {
        q1(0)*q2(3) + q1(1)*q2(2) + -q1(2)*q2(1) + q1(3)*q2(0),
                -q1(0)*q2(2) + q1(1)*q2(3) + q1(2)*q2(0) + q1(3)*q2(1),
                q1(0)*q2(1) + -q1(1)*q2(0) + q1(2)*q2(3) + q1(3)*q2(2),
                -q1(0)*q2(0) + -q1(1)*q2(1) + -q1(2)*q2(2) + q1(3)*q2(3)
    };
    q3 = normalise(q3);
    if ( q3(3) < 0 ) { q3 = -q3; }
    arma::vec rv { 2.0*q3(0), 2.0*q3(1), 2.0*q3(2) };
    return rv;
}

arma::mat base::q2rm(arma::vec& q) {
    arma::mat rm(3,3);
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

arma::vec base::rm2q(arma::mat& rm) {
    arma::vec q { 0.0, 0.0, 0.0, 1.0 };
    q(0) = 0.5 * sqrt(1.0 + rm(0,0) - rm(1,1) - rm(2,2)) * sgn( rm(1,2)-rm(2,1) );
    q(1) = 0.5 * sqrt(1.0 - rm(0,0) + rm(1,1) - rm(2,2)) * sgn( rm(2,0)-rm(0,2) );
    q(2) = 0.5 * sqrt(1.0 - rm(0,0) - rm(1,1) + rm(2,2)) * sgn( rm(0,1)-rm(1,0) );
    q(3) = 0.5 * sqrt(1.0 + rm(0,0) + rm(1,1) + rm(2,2));
    q = normalise(q);
    if (q(3) < 0.0) q = -q;
    return q;
}

double base::sgn(double x) { // nonstandard signum return +1 for 0
    if (x >= 0.0) return 1.0;
    if (x < 0.0) return -1.0;
    return 1.0;
}
