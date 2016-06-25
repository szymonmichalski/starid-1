#ifndef SOLVER_H
#define SOLVER_H

#include "model.h"
#include <armadillo>

namespace svm {


class Train {

public:
    Train(svm::Model& model);

    bool IsStoppingCriteriaTrue();

    struct WorkingSet {
        uint i;
        uint j;
    };
    WorkingSet workingset;
    WorkingSet SelectWorkingSet();


private:

};

}

#endif // SOLVER_H
