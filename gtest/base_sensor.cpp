#include "geometry.h"
#include "catalog.h"
#include "sensor.h"

#include <chrono>
//#include <iostream>
//#include <string>
#include <armadillo>
#include "gtest/gtest.h"

double UnixTimeToJ2000Offset = 946684800.0;
double RaOrion = 75.0 * arma::datum::pi / 180.0;
double DecOrion = 0.0 * arma::datum::pi / 180.0;
double RaCass = 0.0 * arma::datum::pi / 180.0;
double DecCass = 60.0 * arma::datum::pi / 180.0;

TEST(base_sensor, endtoend)
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
    EXPECT_EQ(obs.tpc.n_rows, (unsigned)25);
}
