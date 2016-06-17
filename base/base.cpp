#include "pointing.h"
#include "catalog.h"
#include "sensor.h"
#include "training.h"
#include <armadillo>

int main()
{
    arma::arma_rng::set_seed_random();

    std::string fcatalog = "../../SKYMAP_SKY2000_V5R4.txt";
    double t = 0.0;
    double mv = 6.5;
    base::Catalog catalog(fcatalog, t, mv);

    double fov = 4.0 * arma::datum::pi / 180.0;
    base::Sensor sensor(fov, mv);

    double ra = 0.0 * arma::datum::pi / 180.0;
    double dec = 60.0 * arma::datum::pi / 180.0;
    double yaw = 0.0 * arma::datum::pi / 180.0;
    base::Pointing pointing(ra, dec, yaw);

    sensor.Click(catalog, pointing);

    uint starndx = 4030;
    base::Training training(catalog, sensor, starndx);

    return 0;
}

