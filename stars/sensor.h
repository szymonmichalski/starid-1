#ifndef SENSOR_H
#define SENSOR_H

#include "stars.h"
#include <armadillo>

namespace stars {

class Sensor {
public:

    Sensor(std::string fcatalog, double mv, double fov);

    stars::Stars stars;

    arma::mat makeStarImage(uint starndx);

    std::vector<int> starsvec_ndxs; // starvec ndxs

    double fov; // fov radius, radians
    double mv; // dimmest star
    double noise; // pointing vector noise equivalent angle, arcseconds

    arma::mat l1_uvec;
    arma::mat l1_hv;
    arma::vec l1_starndx;
    arma::vec l1_mag;

    void status();

private:


    double ra, dec, yaw;
    arma::vec pointing; // pointing vec

    arma::mat rotationMatrix();
    arma::vec quaternion();
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
