#ifndef TRIPLETS_H
#define TRIPLETS_H

#include "sensor.h"
#include "pairs_over_whole_sky.h"

namespace triangles {

struct Triangle {
    arma::vec uva;
    arma::vec uvb;
    arma::vec uvc;
    double angab;
    double angac;
    double angbc;
};

class TrianglesInStarImage
{

public:

    TrianglesInStarImage(stars::Sensor &sensor, double triangle_tol, uint max_triangles);
    void recognizeTriangleInStarImage();

private:

    triangles::PairsOverWholeSky pairsOverWholeSky;
    stars::Sensor &sensor;
    double triangle_tol;
    uint max_triangles;
    uint num_stars;
    uint cur_triangle;
};

}

#endif
