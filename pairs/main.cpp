#include "pairs.h"
#include "triplets.h"
#include "../base/pointing.h"
#include "../base/catalog.h"
#include "../base/sensor.h"
#include <armadillo>

int main()
{
    arma::arma_rng::set_seed_random();

    std::string fcatalog = "../../SKYMAP_SKY2000_V5R4.txt";
    double t = 0.0;
    double mv = 6.5;
    double fov = 4.0 * arma::datum::pi / 180.0;
    double ra = 0.0 * arma::datum::pi / 180.0;
    double dec = 60.0 * arma::datum::pi / 180.0;
    double yaw = 0.0 * arma::datum::pi / 180.0;
    base::Pointing pointing(ra, dec, yaw);

    base::Catalog catalog(fcatalog, t, mv);
    base::Sensor sensor(fov, mv);
    sensor.L1a(catalog, pointing);

    pairs::Pairs pairs(catalog, fov);
    pairs.Status();

    double tol = 60 * arma::datum::pi / 648e3;
    pairs::Triplets triplets(sensor.l1a, 1e3);
    while (triplets.IsMoreTriplets()) {
        pairs::Triplet triplet = triplets.GetTriplet(tol);
        if (triplets.is_triplet_good) {
            std::vector<int> l1ab = pairs.Candidates(triplet.angab, 0.05*tol);
            std::vector<int> l1ac = pairs.Candidates(triplet.angac, 0.05*tol);
            std::vector<int> l1bc = pairs.Candidates(triplet.angbc, 0.05*tol);
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
            int a = 1;
        }
    }

    return 0;
}
