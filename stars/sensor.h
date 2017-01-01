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

};

}

#endif // SENSOR_H
