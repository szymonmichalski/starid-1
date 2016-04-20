#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <armadillo>

namespace base {

struct Pointing {
    Pointing();
    Pointing(double ra, double dec, double yaw);
    arma::vec uv;
    double yaw;
    arma::mat RotationMatrix();
    arma::vec Quaternion();
};

arma::vec qmult(arma::vec& q1, arma::vec& q2);
arma::vec qconj(arma::vec& q);
arma::vec rv2q(arma::vec& rv);
arma::vec q2rv(arma::vec& q);
arma::vec qdif2rv(arma::vec& q1, arma::vec& q2);
arma::mat q2rm(arma::vec& q);
arma::vec rm2q(arma::mat& rm);
double sgn(double x);
}
#endif
