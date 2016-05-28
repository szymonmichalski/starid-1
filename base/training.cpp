#include "training.h"

base::Training::Training(Catalog& catalog, Sensor& sensor, uint starndx) {
    using namespace arma;

    TrainingSet trainingset;
    trainingset.starndx = starndx;
    trainingset.inclass = 10;
    trainingset.outclass = 10;

    arma_rng::set_seed_random();  // set the seed to a random value
    ivec rndstarndxs = randi<imat>(trainingset.outclass, distr_param(0, catalog.stars.size()-1));

    std::cout << rndstarndxs << "\n";
}

void base::Training::Status() {

}
