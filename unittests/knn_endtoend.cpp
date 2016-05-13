#include "../base/pointing.h"
#include "../base/catalog.h"
#include "../base/sensor.h"
#include "../knn/l2.h"

#include <armadillo>
#include "gtest/gtest.h"

TEST(knn_main, endtoend)
{
    using namespace arma;
    std::string fcatalog = "../../SKYMAP_SKY2000_V5R4.txt";
    double t = 0.0;
    double mv = 6.5;
    double fov = 4.0 * datum::pi / 180.0;
    base::Catalog catalog(fcatalog, t, mv);
    base::Sensor sensor(fov, mv);

    knn::L2 l2(catalog, sensor);
//    l2.StatusFeatures();
//    l2.StatusOrthogonality();

    uint catndx1 = 4030;
    std::string star_name = catalog.stars[catndx1].star_name;
    double ra = catalog.stars[catndx1].ra;
    double dec = catalog.stars[catndx1].dec;
    double yaw = 0.0 * arma::datum::pi / 180.0;
    base::Pointing p(ra, dec, yaw);
    sensor.Obs(catalog, p);
    vec fv = sensor.l2.fv1;
    uint catndx2 = l2.Classify(fv);

    EXPECT_EQ(catndx1, catndx2);

}
