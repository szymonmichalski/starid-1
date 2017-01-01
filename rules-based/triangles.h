#ifndef TRIPLETS_H
#define TRIPLETS_H

#include "sensor.h"
#include "pairs_over_whole_sky.h"

namespace rules {

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

    Triangles(stars::Sensor& sensor,
              rules::PairsOverWholeSky& pairs,
              double triangle_tol,
              int max_triangles);
    int identifyCentralStar();

private:

    rules::PairsOverWholeSky pairsOverWholeSky;
    stars::Sensor& sensor;
    double triangle_tol;
    uint max_triangles;
    uint num_stars;
    uint cur_triangle;
};

}

#endif
