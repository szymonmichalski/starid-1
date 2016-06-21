#ifndef SVMTRAIN_H
#define SVMTRAIN_H

#include "../base/pointing.h"
#include "../base/catalog.h"
#include "../base/sensor.h"
#include "../base/training.h"
#include <armadillo>

namespace svm {

struct SvmProblem
{
    int l;
    arma::vec y;
    double gamma;
    double eps;
    double C;
};

class SvmTrain {

public:
    SvmTrain(base::Training& trainingset);

private:

};

}

#endif // SVMTRAIN_H
