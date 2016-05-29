#include "pointing.h"
#include "catalog.h"
#include "sensor.h"
#include "pairs.h"
#include "triplets.h"

#include <armadillo>
#include "gtest/gtest.h"

TEST(ptq_main, endtoend)
{
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

    ptq::Pairs pairs(catalog, fov);

    double tol = 60 * arma::datum::pi / 648e3;
    ptq::Triplets triplets(sensor.l1, 1e3);
    EXPECT_EQ(triplets.n, 23);
}
