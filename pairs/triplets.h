#ifndef TRIPLETS_H
#define TRIPLETS_H

#include "../base/sensor.h"

namespace pairs {

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
    Triplets(base::L1& obs, uint nlimit);
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
