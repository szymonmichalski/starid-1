#ifndef SVMTRAIN_H
#define SVMTRAIN_H

#include "../base/pointing.h"
#include "../base/catalog.h"
#include "../base/sensor.h"
#include <armadillo>

namespace svm {

class SvmTrain {
public:
    SvmTrain(arma::mat& examples, arma::vec& labels);

private:
    arma::mat examples;
    arma::vec labels;
};

}

#endif // SVMTRAIN_H
