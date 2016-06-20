#ifndef SVM_H
#define SVM_H

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

}

#endif // SVM_H
