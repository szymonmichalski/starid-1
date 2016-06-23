#include "model.h"

svm::Model::Model(base::Training &trainingset)
    : examples(trainingset.examples),
      labels(trainingset.labels)
{
    using namespace arma;

    tssize = labels.n_rows;
    gamma = 1;
    epsilon = 0.001;
    regparam = 1;

    alpha.zeros(tssize);
    K.eye(tssize,tssize);
    for (uint i = 0; i < tssize; ++i) {
        for (uint j = i+1; j < tssize; ++j) {
             K(i,j) = exp( -gamma * dot( examples.row(i), examples.row(j) ) ); // rbf kernel
             K(j,i) = K(i,j);
        }
    }

}
