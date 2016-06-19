#include "../base/pointing.h"
#include "../base/catalog.h"
#include "../base/sensor.h"
#include "../base/training.h"
#include "svmtrain.h"
#include <armadillo>

int main()
{
    using namespace arma;
    arma::arma_rng::set_seed_random();

    base::Training trainingset;

    svm::SvmTrain svmtrain(trainingset);

    return 0;
}
