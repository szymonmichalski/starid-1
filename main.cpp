#include <chrono>
#include <string>

#include "util.h"
#include "catalog.h"

int main()
{
    std::chrono::time_point<std::chrono::system_clock> tcurrent {std::chrono::system_clock::now()};
    double years_from_j2000 {(double(std::chrono::system_clock::to_time_t(tcurrent)) - util::kUnixTimeToJ2000Offset) / 31557600.0}; // julian years
    double max_mv {6.5};
    std::string catalog_file {"../SKYMAP_SKY2000_V5R4.txt"};

    catalog::Catalog catalog(catalog_file, years_from_j2000, max_mv);
    double radius {4.0*util::pi/180.0};
//    std::vector<int> indexes = catalog.StarsNearPoint(util::kRaOrion, util::kDecOrion, radius);
    std::vector<int> indexes = catalog.StarsNearPoint(util::kRaCass, util::kDecCass, radius);

    for (auto ndx : indexes) {
        catalog.printStar(ndx);
    }

    return 0;
}

