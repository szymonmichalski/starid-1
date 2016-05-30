#ifndef SIMPLE_H
#define SIMPLE_H

#include "../base/pointing.h"
#include "../base/catalog.h"
#include "../base/sensor.h"

#include <armadillo>

namespace knn {

class Simple {
public:
    Simple(base::Catalog& catalog, base::Sensor& sensor);
    arma::Mat<double> l2a;
    void StatusFeatures();
    void StatusOrthogonality();
    uint Classify(arma::vec& fv);
private:
};

}

#endif
