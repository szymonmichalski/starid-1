#ifndef TRAINING_H
#define TRAINING_H

#include <armadillo>

namespace training {

struct TrainingSet {
    arma::mat examples; // n x l matrix of n dimensional feature vectors
    arma::vec labels; // l x 1 vector of class labels -1 or 1
};

class Training {
public:
private:
};

}

#endif // TRAINING_H
