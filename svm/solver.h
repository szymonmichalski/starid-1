#ifndef SOLVER_H
#define SOLVER_H

#include "kernel.h"
#include <armadillo>

namespace svm {

class Solver {

public:
    void Solve(svm::SvmProblem& problem, svm::Kernel& kernel);

private:

};

}

#endif // SOLVER_H
