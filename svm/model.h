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

    uint tsetsize; // l
    double gamma; // rbf kernel param
    double epsilon;
    double regparam; // C > 0 regularization param

    arma::vec alpha;
    arma::mat kernel;

private:

};

}

#endif // SVMPROBLEM_H
