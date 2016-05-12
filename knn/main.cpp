#include "../base/pointing.h"
#include "../base/catalog.h"
#include "../base/sensor.h"
#include "l2.h"

#include <armadillo>

int main()
{
    using namespace arma;
    std::string fcatalog = "../../SKYMAP_SKY2000_V5R4.txt";
    double t = 0.0;
    double mv = 6.5;
    double fov = 4.0 * datum::pi / 180.0;
    base::Catalog catalog(fcatalog, t, mv);
    base::Sensor sensor(fov, mv);

    knn::L2 l2(catalog, sensor);
    l2.StatusFeatures();
//    l2.StatusOrthogonality();

    double ra = 0.0 * arma::datum::pi / 180.0;
    double dec = 60.0 * arma::datum::pi / 180.0;
    double yaw = 0.0 * arma::datum::pi / 180.0;
    base::Pointing p(ra, dec, yaw);
    sensor.Obs(catalog, p);
    vec fv = sensor.l2.fv1;

    return 0;
}
