#ifndef TRIPLETS_H
#define TRIPLETS_H

#include "sensor.h"

namespace triangles {

struct Triplet {
    arma::vec uva;
    arma::vec uvb;
    arma::vec uvc;
    double angab;
    double angac;
    double angbc;
};

class Triplets
{
public:
    Triplets();
//    Triplets(stars::L1& obs, uint nlimit);
    Triplet GetTriplet(double tol);
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
