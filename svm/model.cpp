#include "model.h"

svm::Model::Model(base::Training &trainingset)
    : examples(trainingset.examples),
      labels(trainingset.labels)
{
    using namespace arma;

    l = labels.n_rows;
    gamma = 1;
    epsilon = 0.001;
    C = 1;

    alpha.zeros(l);
    K.eye(l,l);
    for (uint i = 0; i < l; ++i) {
        for (uint j = i+1; j < l; ++j) {
             K(i,j) = exp( -gamma * dot( examples.row(i), examples.row(j) ) ); // rbf kernel
             K(j,i) = K(i,j);
        }
    }

}
