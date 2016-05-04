#include "angles.h"
#include "triplets.h"
#include "../base/pointing.h"
#include "../base/catalog.h"
#include "../base/sensor.h"

#include <chrono>
#include <armadillo>

double UnixTimeToJ2000Offset = 946684800.0;
double RaOrion = 75.0 * arma::datum::pi / 180.0;
double DecOrion = 0.0 * arma::datum::pi / 180.0;
double RaCass = 0.0 * arma::datum::pi / 180.0;
double DecCass = 60.0 * arma::datum::pi / 180.0;

int main()
{
    std::chrono::time_point<std::chrono::system_clock> tcurrent {std::chrono::system_clock::now()};
    double years_from_j2000 {(double(std::chrono::system_clock::to_time_t(tcurrent)) - UnixTimeToJ2000Offset) / 31557600.0}; // julian years
    double fovradius {4.0 * arma::datum::pi / 180.0};
    double mv {6.5};

    std::string catalog_file {"../../SKYMAP_SKY2000_V5R4.txt"};
    base::Catalog catalog(catalog_file, years_from_j2000, mv);

    double yaw {0.0 * arma::datum::pi / 180.0};
    base::Pointing pointing(RaCass, DecCass, yaw);
    base::Sensor sensor(fovradius, mv);
    sensor.SetPointing(pointing);
    base::L1 obs = sensor.Level1(catalog);

    pairs::Angles angles(catalog, fovradius);
    angles.Status();

    double tol = 60 * arma::datum::pi / 648e3;
    pairs::Triplets triplets(obs, 1e3);
    while (triplets.IsMoreTriplets()) {
        pairs::Triplet triplet = triplets.GetTriplet(tol);
        if (triplets.is_triplet_good) {
            std::vector<int> l1ab = angles.Candidates(triplet.angab, 0.05*tol);
            std::vector<int> l1ac = angles.Candidates(triplet.angac, 0.05*tol);
            std::vector<int> l1bc = angles.Candidates(triplet.angbc, 0.05*tol);
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
