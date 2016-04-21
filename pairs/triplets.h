#ifndef TRIPLETS_H
#define TRIPLETS_H

#include "../base/sensor.h"

namespace pairs {

class Triplets
{
public:
    Triplets();
    Triplets(base::Obs& obs);
    uint n;
    uint curtriplet;
    arma::mat mata;
    arma::mat matb;
    arma::mat matc;
    arma::mat getTriplet();
};

}

#endif
