#ifndef SENSOR_H
#define SENSOR_H

#include "sky.h"
#include <armadillo>

namespace stars {

class Sensor {
public:

    Sensor(std::string fcatalog, double mv, double fov);

    stars::Sky sky;

    arma::mat makeStarImage(uint starndx);

    std::vector<int> starsvec_ndxs; // starvec ndxs

    double mv; // dimmest star
    double fov; // fov radius, radians
    double noise; // pointing vector noise equivalent angle, arcseconds

    arma::mat l1_uvec;
    arma::mat l1_hv;
    arma::vec l1_starndx;
    arma::vec l1_mag;

    void status();

private:

    double ra, dec, yaw;
    arma::vec pointing; // pointing vec

    arma::mat rotationMatrix(arma::vec& pointing, double yaw = 0);

    double sgn(double x);

    arma::vec rm2q(arma::mat& rm);

    arma::vec quaternion(arma::vec& pointing, double yaw);

    arma::vec qmult(arma::vec& q1, arma::vec& q2);

    arma::vec qconj(arma::vec& q);

    arma::vec rv2q(arma::vec& rv);

    arma::vec q2rv(arma::vec& q);

    arma::vec qdif2rv(arma::vec& q1, arma::vec& q2a);

    arma::mat q2rm(arma::vec& q);

};

}

#endif // SENSOR_H
