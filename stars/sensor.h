#ifndef SENSOR_H
#define SENSOR_H

#include "stars.h"
#include <armadillo>

namespace stars {

class Sensor {
public:
    Sensor();
    stars::Stars stars; // constructs stars object
    arma::mat Image(uint starndx);

    std::vector<int> starsvec_ndxs; // starvec ndxs
    std::vector<double> l1_mags;
    arma::mat l1_uvecs;
    arma::mat l1_hv;

    void Status();

private:
    double fov; // fov radius, radians
    double mv; // dimmest star
    double noise; // pointing vector noise equivalent angle, arcseconds

    double ra, dec, yaw;
    arma::vec pointing; // pointing vec

    arma::mat RotationMatrix();
    arma::vec Quaternion();
    arma::vec qmult(arma::vec& q1, arma::vec& q2);
    arma::vec qconj(arma::vec& q);
    arma::vec rv2q(arma::vec& rv);
    arma::vec q2rv(arma::vec& q);
    arma::vec qdif2rv(arma::vec& q1, arma::vec& q2);
    arma::mat q2rm(arma::vec& q);
    arma::vec rm2q(arma::mat& rm);
    double sgn(double x);
};

}

#endif // SENSOR_H
