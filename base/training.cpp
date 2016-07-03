#include "training.h"

base::Training::Training() {
    using namespace arma;

    arma::arma_rng::set_seed_random();

    std::string fcatalog = "SKYMAP_SKY2000_V5R4.txt";
    double t = 0.0;
    double mv = 6.5;
    base::Catalog catalog(fcatalog, t, mv);

    double fov = 4.0 * arma::datum::pi / 180.0;
    base::Sensor sensor(fov, mv);

    examples.zeros(200, 784);
    labels = zeros(200);

    uint catndx1 = 4030;
    double ra1 = catalog.stars[catndx1].ra;
    double dec1 = catalog.stars[catndx1].dec;
    double yaw1 = 0.0 * arma::datum::pi / 180.0;
    base::Pointing p1(ra1, dec1, yaw1);
    for (uint i = 0; i < 100; ++i) {
        sensor.Click(catalog, p1);
        examples.row(i) = trans(sensor.l2b.fv);
        labels(i) = 1.0;
    }

    uint catndx2 = 4000;
    double ra2 = catalog.stars[catndx2].ra;
    double dec2 = catalog.stars[catndx2].dec;
    double yaw2 = 0.0 * arma::datum::pi / 180.0;
    base::Pointing p2(ra2, dec2, yaw2);
    for (uint i = 100; i < 200; ++i) {
        sensor.Click(catalog, p2);
        examples.row(i) = trans(sensor.l2b.fv);
        labels(i) = -1.0;
    }

    //    ivec outclassndxs = randi<imat>(trainingset.outclass, distr_param(0, catalog.stars.size()-1));

}

void base::Training::Status() {

}
