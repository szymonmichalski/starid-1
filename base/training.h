#ifndef TRAINING_H
#define TRAINING_H

#include "catalog.h"
#include "sensor.h"
#include "pointing.h"
#include <armadillo>

namespace base {

struct TrainingSet {
    uint starndx; // star to train for
    uint inclass; //in class examples count
    uint outclass; // out of class examples count
};

class Training {
public:
    Training(Catalog& catalog, Sensor& sensor, uint starndx);
    void Status();
private:
};

}

#endif // TRAINING_H
