#include "triangles.h"
#include "sensor.h"
#include <armadillo>

int main() {
    arma::arma_rng::set_seed_random();

    std::string f_catalog = "/home/noah/dev/SKYMAP_SKY2000_V5R4.txt";
    double mv             = 6.5;
    double fov            = 4.0 * arma::datum::pi / 180.0;
    uint starndx          = 800;
    double triplets_tol   = 60 * arma::datum::pi / 648e3;
    uint triplets_max     = 1e3;

    stars::Sensor sensor(f_catalog, mv, fov);
    triangles::Triangles triangles(sensor, triplets_tol, triplets_max);

    sensor.Image(starndx);
    triangles.StarPairsInImage(sensor);
    uint starndx2 = triangles.MatchTriangles();

    return 0;
}



