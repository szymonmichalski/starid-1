#include "problem.h"
#include "solver.h"

#include "training.h"
#include <armadillo>

int main()
{

    base::Training trainingset;

    svm::Problem problem(trainingset);

    svm::Solver solver(problem);

    return 0;
}
