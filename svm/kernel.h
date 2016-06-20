#ifndef KERNEL_H
#define KERNEL_H

#include <armadillo>
#include "svm.h"

namespace svm {

class Kernel {

public:
    Kernel(svm::SvmProblem& problem);

};

}

#endif // KERNEL_H
