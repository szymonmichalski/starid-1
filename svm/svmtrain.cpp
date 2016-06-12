#include "svmtrain.h"

svm::SvmTrain::SvmTrain(arma::mat& examples, arma::vec& labels)
    : examples(examples), labels(labels)
{

}
