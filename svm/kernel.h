#ifndef KERNEL_H
#define KERNEL_H

#include <armadillo>
#include "svm.h"

namespace svm {

class Kernel {

public:
    Kernel(uint l, SvmParameters& param);

};

}

#endif // KERNEL_H
