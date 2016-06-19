#ifndef TRAINING_H
#define TRAINING_H

#include "catalog.h"
#include "sensor.h"
#include "pointing.h"
#include <armadillo>

namespace base {

class Training {
public:
    Training();
    void Status();

    arma::mat examples;
    arma::vec labels;

private:
};

}

#endif // TRAINING_H
