#include "model.h"
#include "train.h"

#include "training.h"
#include <armadillo>

int main()
{

    base::Training trainingset;

    svm::Model model(trainingset);

    svm::Train train(model);

    return 0;
}
