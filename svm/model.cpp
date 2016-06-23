#include "model.h"

svm::Model::Model(base::Training &trainingset)
    : examples(trainingset.examples),
      labels(trainingset.labels)
{
    using namespace arma;

    tsetsize = labels.n_rows;
    gamma = 1;
    epsilon = 0.001;
    regparam = 1;

    alpha.zeros(tsetsize);
    kernel.eye(tsetsize,tsetsize);
    for (uint i = 0; i < tsetsize; ++i) {
        for (uint j = i+1; j < tsetsize; ++j) {
             rowvec vecdiff = examples.row(i) - examples.row(j);
             kernel(i,j) = exp( -gamma * dot( vecdiff, vecdiff ) ); // rbf kernel
             kernel(j,i) = kernel(i,j);
        }
    }

}
