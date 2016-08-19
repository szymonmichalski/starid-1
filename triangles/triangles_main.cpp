#include "pairs.h"
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

    arma::mat img = sensor.Image(starndx);

    triangles::Pairs pairs(sensor, fov);
    triangles::Triangles triplets(sensor, triplets_max);

    while (triplets.IsMoreTriplets()) {

        triangles::Triangle triplet = triplets.GetTriplet(triplets_tol);

        if (triplets.is_triplet_good) {

            std::vector<int> l1ab = pairs.Candidates(triplet.angab, 0.05 * triplets_tol);
            std::vector<int> l1ac = pairs.Candidates(triplet.angac, 0.05 * triplets_tol);
            std::vector<int> l1bc = pairs.Candidates(triplet.angbc, 0.05 * triplets_tol);
            std::vector<int> l2abac;
            std::vector<int> l2babc;
            std::vector<int> l2cacb;
            std::set_intersection(l1ab.begin(), l1ab.end(),
                                  l1ac.begin(), l1ac.end(),
                                  back_inserter(l2abac));
            std::set_intersection(l1ab.begin(), l1ab.end(),
                                  l1bc.begin(), l1bc.end(),
                                  back_inserter(l2babc));
            std::set_intersection(l1ac.begin(), l1ac.end(),
                                  l1bc.begin(), l1bc.end(),
                                  back_inserter(l2cacb));

        }
    }

    return 0;
}



