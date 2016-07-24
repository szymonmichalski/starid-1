#ifndef KNNTRAIN_H
#define KNNTRAIN_H

#include "../stars/stars.h"
#include "../stars/sensor.h"
#include <armadillo>

namespace convnet {

class KnnTrain {
public:
    KnnTrain(stars::Stars& catalog, stars::Sensor& sensor);
    void StatusFeatures();
    void StatusOrthogonality();
    uint Classify(arma::vec& fv);

    arma::Mat<double> fvs;

private:
};

}

#endif
