#include "pointing.h"

#include <cassert>

stars::Pointing::Pointing() {
    double ra = 0.0 * arma::datum::pi / 180.0;
    double dec = 60.0 * arma::datum::pi / 180.0;
    double yaw = 0.0 * arma::datum::pi / 180.0;
    init(ra, dec, yaw);
}
stars::Pointing::Pointing(double ra, double dec, double yaw) {
    init(ra, dec, yaw);
}
void stars::Pointing::init(double ra, double dec, double yaw) {
    uv = {1, 0, 0};
    uv(0) = std::cos(ra) * std::cos(dec);
    uv(1) = std::sin(ra) * std::cos(dec);
    uv(2) = std::sin(dec);
    uv = arma::normalise(uv);
    double err = std::abs(arma::norm(uv) - 1.0);
    assert(err < 1e-10);
}

arma::mat stars::Pointing::RotationMatrix() {
    arma::mat rm;
    rm.eye(3,3);
    arma::vec bz = uv;
    arma::vec iz = { 0.0, 0.0, 1.0 };
    arma::vec b1x = arma::cross(bz,iz);
    b1x = arma::normalise(b1x);
    arma::vec b1y = arma::cross(bz,b1x);
    b1y = arma::normalise(b1y);
    arma::vec bx = std::cos(yaw) * b1x + std::sin(yaw) * b1y;
    arma::vec by = std::sin(yaw) * b1x + std::cos(yaw) * b1y;
    rm.col(0) = arma::normalise(bx);
    rm.col(1) = arma::normalise(by);
    rm.col(2) = bz;
    double err = std::abs(arma::det(rm) - 1.0);
    assert(err < 1e-10);
    return rm;
}

arma::vec stars::Pointing::Quaternion() {
    arma::mat rm = RotationMatrix();
    arma::vec q;
    q.set_size(4);
    q = rm2q(rm);
    q = arma::normalise(q);
    assert(arma::norm(q) == 1.0);
    return q;
}

arma::vec stars::qmult(arma::vec& q1, arma::vec& q2) {
    arma::vec q3 {
        q1(0)*q2(3) + q1(1)*q2(2) + -q1(2)*q2(1) + q1(3)*q2(0),
                -q1(0)*q2(2) + q1(1)*q2(3) + q1(2)*q2(0) + q1(3)*q2(1),
                q1(0)*q2(1) + -q1(1)*q2(0) + q1(2)*q2(3) + q1(3)*q2(2),
                -q1(0)*q2(0) + -q1(1)*q2(1) + -q1(2)*q2(2) + q1(3)*q2(3)
    };
    q3 = arma::normalise(q3);
    if (q3(3) < 0.0) q3 = -q3;
    return q3;
}

arma::vec stars::qconj(arma::vec& q) {
    arma::vec q2 { -q(0), -q(1), -q(2), q(3) };
    return q2;
}

arma::vec stars::rv2q(arma::vec& rv) {
    arma::vec q { rv(0)/2, rv(1)/2, rv(2)/2, 1 };
    q = arma::normalise(q);
    if (q(3) < 0.0) q = -q;
    return q;
}

arma::vec stars::q2rv(arma::vec& q) {
    arma::vec rv { 2*q(0), 2*q(1), 2*q(2) };
    return rv;
}

arma::vec stars::qdif2rv(arma::vec& q1, arma::vec& q2a) {
    arma::vec q2 { -q2a(0), -q2a(1), -q2a(2), q2a(3) };
    arma::vec q3 {
        q1(0)*q2(3) + q1(1)*q2(2) + -q1(2)*q2(1) + q1(3)*q2(0),
                -q1(0)*q2(2) + q1(1)*q2(3) + q1(2)*q2(0) + q1(3)*q2(1),
                q1(0)*q2(1) + -q1(1)*q2(0) + q1(2)*q2(3) + q1(3)*q2(2),
                -q1(0)*q2(0) + -q1(1)*q2(1) + -q1(2)*q2(2) + q1(3)*q2(3)
    };
    q3 = arma::normalise(q3);
    if ( q3(3) < 0 ) { q3 = -q3; }
    arma::vec rv { 2.0*q3(0), 2.0*q3(1), 2.0*q3(2) };
    return rv;
}

arma::mat stars::q2rm(arma::vec& q) {
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

arma::vec stars::rm2q(arma::mat& rm) {
    arma::vec q { 0.0, 0.0, 0.0, 1.0 };
    q(0) = 0.5 * sqrt(1.0 + rm(0,0) - rm(1,1) - rm(2,2)) * sgn( rm(1,2)-rm(2,1) );
    q(1) = 0.5 * sqrt(1.0 - rm(0,0) + rm(1,1) - rm(2,2)) * sgn( rm(2,0)-rm(0,2) );
    q(2) = 0.5 * sqrt(1.0 - rm(0,0) - rm(1,1) + rm(2,2)) * sgn( rm(0,1)-rm(1,0) );
    q(3) = 0.5 * sqrt(1.0 + rm(0,0) + rm(1,1) + rm(2,2));
    q = arma::normalise(q);
    if (q(3) < 0.0) q = -q;
    return q;
}

double stars::sgn(double x) { // nonstandard signum return +1 for 0
    if (x >= 0.0) return 1.0;
    if (x < 0.0) return -1.0;
    return 1.0;
}
