#ifndef SVMTRAIN_H
#define SVMTRAIN_H

#include "../base/pointing.h"
#include "../base/catalog.h"
#include "../base/sensor.h"
#include "../base/training.h"
#include <armadillo>

namespace svm {

class SvmTrain {

public:
    SvmTrain(base::Training& trainingset);

private:

};

}

#endif // SVMTRAIN_H
