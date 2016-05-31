#include "../base/pointing.h"
#include "../base/catalog.h"
#include "../base/sensor.h"
#include "simple.h"
#include <armadillo>

int main()
{
    arma::arma_rng::set_seed_random();

    using namespace arma;
    std::string fcatalog = "../../SKYMAP_SKY2000_V5R4.txt";
    double t = 0.0;
    double mv = 6.5;
    double fov = 4.0 * datum::pi / 180.0;
    base::Catalog catalog(fcatalog, t, mv);
    base::Sensor sensor(fov, mv);

    knn::Simple simple(catalog, sensor);
    simple.StatusFeatures();
//    simple.StatusOrthogonality();

    uint catndx1 = 4030;
    std::string star_name = catalog.stars[catndx1].star_name;
    double ra = catalog.stars[catndx1].ra;
    double dec = catalog.stars[catndx1].dec;
    double yaw = 0.0 * arma::datum::pi / 180.0;
    base::Pointing p(ra, dec, yaw);
    sensor.L1a(catalog, p);
    vec fv = sensor.l2a.fv;
    uint catndx2 = simple.Classify(fv);

    return 0;
}
