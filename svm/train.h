#ifndef TRAIN_H
#define TRAIN_H

#include "model.h"
#include <armadillo>

namespace svm {


class Train {

public:
    Train(svm::Model& model);
    bool WorkingSet(); // returns stopping criteria bool
    void MainLoop();
    void SubProblem();

    double epsilon;
    double lval;
    double Cval;
    double biasval;
    arma::vec bvec;
    arma::vec pvec;
    arma::vec yvec;
    arma::mat Kmat;
    arma::mat Qmat;
    arma::vec alphavec;
    arma::vec gradient;
    uint wsi;
    uint wsj;

private:
};

}

#endif // SOLVER_H
