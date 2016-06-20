#ifndef SVM_H
#define SVM_H

#include <armadillo>

namespace svm {

struct SvmProblem
{
    int l;
    arma::vec y;
};

struct SvmParameters
{
    enum kernel_type {LINEAR, RBF};
    double gamma;	/* for poly/rbf/sigmoid */
    double eps;	/* stopping criteria */
    double C;	/* for C_SVC, EPSILON_SVR and NU_SVR */
    int nr_weight;		/* for C_SVC */
    arma::ivec weight_label;	/* for C_SVC */
    arma::vec weight;		/* for C_SVC */
    bool shrinking;	/* use the shrinking heuristics */
    bool probability; /* do probability estimates */
};

}

#endif // SVM_H
