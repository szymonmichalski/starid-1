#include <chrono>
#include <string>

#include "def.h"
#include "catalog.h"

int main()
{
    std::chrono::time_point<std::chrono::system_clock> tcurrent {std::chrono::system_clock::now()};
    double years_from_j2000 = (double(std::chrono::system_clock::to_time_t(tcurrent)) - kUnixTimeToJ2000Offset) / 31557600.0; // julian years
    double max_mv = 7.2;
    std::string catalog_file {"../SKYMAP_SKY2000_V5R4.txt"};

    Catalog catalog(catalog_file, years_from_j2000, max_mv);

    return 0;
}

