#include <chrono>
#include <string>
#include <iostream>
#include <armadillo>
using namespace arma;
#include "geometry.h"
#include "catalog.h"
#include "starpairs.h"
#include "sensor.h"

constexpr double UnixTimeToJ2000Offset = 946684800.0;

int main()
{
    std::chrono::time_point<std::chrono::system_clock> tcurrent {std::chrono::system_clock::now()};
    double years_from_j2000 {(double(std::chrono::system_clock::to_time_t(tcurrent)) - UnixTimeToJ2000Offset) / 31557600.0}; // julian years
    double max_mv {6.5};
    std::string catalog_file {"../../SKYMAP_SKY2000_V5R4.txt"};
    double fovradius {4.0*geometry::pi/180.0};

    catalog::Catalog catalog(catalog_file, years_from_j2000, max_mv);
    starpairs::StarPairs pairs(catalog, fovradius);

    geometry::UnitVector pointing(geometry::RaCass, geometry::DecCass);
    std::vector<int> catndxs = catalog.StarsNearPoint(pointing, fovradius);
    std::cout << "stars near cass " << catndxs.size() << "\n";
//    for (auto catndx : catndxs) std::cout << catndx << " " << catalog.stars[catndx].star_name << "\n";

    double yaw {45.0*geometry::pi/180.0};
    sensor::Sensor sensor(pointing, yaw, fovradius);
    sensor::Obs obs = sensor.GetObs(catalog);
    std::cout << sensor.attitude.q << "\n";
    std::cout << obs.uv << "\n";
    std::cout << obs.tpc << "\n";

    return 0;
}


