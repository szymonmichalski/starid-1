#ifndef L2_H
#define L2_H

#include "../base/pointing.h"
#include "../base/catalog.h"
#include "../base/sensor.h"

#include <armadillo>

namespace knn {

class L2 {
public:
    L2(base::Catalog& catalog, base::Sensor& sensor);
    arma::Mat<double> l2a;
    arma::Mat<double> l2b;
    void StatusFeatures();
    void StatusOrthogonality();
private:
};

}

#endif
