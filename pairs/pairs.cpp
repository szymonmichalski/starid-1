#include "angles.h"
#include "triplets.h"
#include "../base/geometry.h"
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
    double max_mv {6.5};
    std::string catalog_file {"../../SKYMAP_SKY2000_V5R4.txt"};
    base::Catalog catalog(catalog_file, years_from_j2000, max_mv);

    double fovradius {4.0 * arma::datum::pi / 180.0};
    double yaw {0.0 * arma::datum::pi / 180.0};
    base::Pointing pointing(RaCass, DecCass, yaw);
    base::Sensor sensor(pointing, fovradius);
    base::Obs obs = sensor.GetObs(catalog);

    double criteria1 = 3600 * arma::datum::pi / 648e3;
    pairs::Angles angles(catalog, fovradius);
    angles.Status();
    pairs::Triplets triplets(obs, 1e3);
    while (triplets.IsMoreTriplets()) {
        pairs::Triplet triplet = triplets.GetTriplet();
        if (abs(triplet.ab - triplet.ac) < criteria1) continue;
        if (abs(triplet.ab - triplet.bc) < criteria1) continue;
        if (abs(triplet.ac - triplet.bc) < criteria1) continue;

    }

    return 0;
}
