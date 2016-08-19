#ifndef TRIPLETS_H
#define TRIPLETS_H

#include "sensor.h"
#include "pairs.h"

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

    Triangles(stars::Sensor &sensor, double triangle_tol, uint max_triangles);

    triangles::Pairs pairs;

    Triangle triangle;
    Triangle GetTriplet(double triangle_tol);

    void StarPairsInImage(stars::Sensor &sensor);
    uint MatchTriangles();

    bool IsMoreTriplets();
    bool is_triplet_good;
    uint n;
    uint curtriplet;
    arma::mat mata;
    arma::mat matb;
    arma::mat matc;

private:

    double triangle_tol;
    uint max_triangles;

};

}

#endif
