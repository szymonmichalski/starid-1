#ifndef TRAIN_H
#define TRAIN_H

#include "model.h"
#include <armadillo>

namespace svm {


class Train {

public:
    Train(svm::Model& model);
    bool StoppingCriteria();
    void SelectWorkingSet(uint& wsndx1, uint& wsndx2);

    double epsilon;
    double lval;
    double Cval;
    arma::vec bvec;
    arma::vec pvec;
    arma::vec yvec;
    arma::mat Qmat;
    arma::vec alphavec;
    arma::vec gradientvec;

private:

};

}

#endif // SOLVER_H
