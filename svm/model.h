#ifndef SVMPROBLEM_H
#define SVMPROBLEM_H

#include "training.h"
#include <armadillo>

namespace svm {

class Model {

public:
    Model(base::Training& trainingset);

    arma::mat examples;
    arma::vec labels;

    uint tssize; // l
    double gamma; // kernel RBF param
    double epsilon;
    double regparam; // C > 0 regularization param

    arma::vec alpha;
    arma::mat K;

private:

};

}

#endif // SVMPROBLEM_H
