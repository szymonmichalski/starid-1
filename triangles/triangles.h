#ifndef TRIPLETS_H
#define TRIPLETS_H

#include "sensor.h"

namespace triangles {

struct Triangle {
    arma::vec uva;
    arma::vec uvb;
    arma::vec uvc;
    double angab;
    double angac;
    double angbc;
};

class Triangles
{

public:

    Triangles(stars::Sensor &sensor, uint triplets_max);

    Triangle GetTriplet(double tol);
    bool IsMoreTriplets();
    bool is_triplet_good;
    uint n;
    uint curtriplet;
    arma::mat mata;
    arma::mat matb;
    arma::mat matc;

private:

};

}

#endif
