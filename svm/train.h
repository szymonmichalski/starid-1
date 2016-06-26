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
    void UpdateEq20();
    void SubProblem();
    void UpdateGradient();

    double epsilon;
    double lval;
    double Cval;
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
    arma::mat Qbb;
    arma::vec alphab;
    arma::vec gradb;
    arma::mat Qbcols;
    arma::vec eq20;
    arma::vec alphavecprev;
};

}

#endif // SOLVER_H
