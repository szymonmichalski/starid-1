#include "model.h"

svm::Model::Model(base::Training &trainingset)
    : examples(trainingset.examples),
      labels(trainingset.labels)
{
    l = labels.n_rows;
    gamma = 1;
    epsilon = 0.001;
    C = 1;

    alpha.zeros(l);
    K.zeros(l, l);
}
