#include "triangles_in_star_image.h"
#include "sensor.h"
#include <armadillo>

int main() {
    arma::arma_rng::set_seed_random();

    std::string fcatalog   = "/home/noah/dev/SKYMAP_SKY2000_V5R4.txt";
    double mv              = 6.5; // sensor upper limit for visual magnitude
    double fov             = 4.0 * arma::datum::pi / 180.0; // sensor field of view
    uint starndx           = 800; // star to be used
    double triangles_tol   = 60 * arma::datum::pi / 648e3; // tolerance for triangle variations
    uint triangles_max     = 1e3; // upper limit for number of triangles

    // create a sensor and make a star image
    stars::Sensor sensor(fcatalog, mv, fov);
    sensor.MakeStarImage(starndx);

    // create star triangles for the image and try to recognize a triangle
    triangles::TrianglesInStarImage triangles(sensor, triangles_tol, triangles_max);
    triangles.RecognizeTriangleInStarImage();

    return 0;
}



