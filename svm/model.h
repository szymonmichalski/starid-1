#ifndef SVMPROBLEM_H
#define SVMPROBLEM_H

#include "training.h"
#include <armadillo>

namespace svm {

class Model {

public:
    Model(base::Training& trainingset);

    double gamma; // rbf kernel param 1/(2*sigma)^2
    double epsilon;
    double Cval; // C > 0 regularization param

    arma::mat xvecs;
    arma::vec yvec;
    uint lval; // l

    arma::vec alphavec;
    arma::mat Kmat;
    arma::mat Qmat;

private:
    arma::rowvec vecdiff;

};

}

#endif // SVMPROBLEM_H
