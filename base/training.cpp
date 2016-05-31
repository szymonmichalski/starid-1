#include "training.h"

base::Training::Training(Catalog& catalog, Sensor& sensor, uint starndx) {
    using namespace arma;

    TrainingSet trainingset;
    trainingset.starndx = starndx;
    trainingset.inclass = 10;
    trainingset.outclass = 10;

    // make the set of inclass examples
    std::string star_name = catalog.stars[starndx].star_name;
    double ra = catalog.stars[starndx].ra;
    double dec = catalog.stars[starndx].dec;
    double yaw = 0.0 * arma::datum::pi / 180.0;
    base::Pointing p(ra, dec, yaw);
    sensor.L1a(catalog, p);
    sensor.L2a();

    // make the set of outclass examples
    arma_rng::set_seed_random();
    ivec outclassndxs = randi<imat>(trainingset.outclass, distr_param(0, catalog.stars.size()-1));


}

void base::Training::Status() {

}
