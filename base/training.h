#ifndef TRAINING_H
#define TRAINING_H

#include "catalog.h"
#include "sensor.h"
#include "pointing.h"
#include <armadillo>

namespace base {

struct TrainingSet {
    arma::mat examples; // n x l matrix of n dimensional feature vectors
    arma::vec labels; // l x 1 vector of class labels -1 (outofclass) or 1 (inclass)
    uint cntinclass; //in class examples count
    uint cntoutofclass; // out of class examples count
};

class Training {
public:
    Training(Catalog& catalog, Sensor& sensor);
    void Status();
private:
};

}

#endif // TRAINING_H
