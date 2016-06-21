#ifndef KERNEL_H
#define KERNEL_H

#include "dualproblem.h"
#include <armadillo>

namespace svm {

class Kernel {

public:
    Kernel(svm::DualProblem& dualproblem);

};

}

#endif // KERNEL_H
