#include "svmproblem.h"
#include "dualproblem.h"
#include "solver.h"

#include "training.h"
#include <armadillo>

int main()
{

    base::Training trainingset;

    svm::SvmProblem svmproblem(trainingset);

    svm::DualProblem dualproblem(svmproblem);

    svm::Solver solver(dualproblem);

    return 0;
}
