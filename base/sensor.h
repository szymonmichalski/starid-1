#ifndef SENSOR_H
#define SENSOR_H

#include "pointing.h"
#include "catalog.h"

namespace base {

struct L1 {
    arma::mat uv;
    arma::mat hv;
    std::vector<int> ndxs;
    std::vector<double> mag;
};

struct L2 {
    arma::Mat<int> pat1;
    arma::Mat<int> pat2;
};

class Sensor {
public:
    Sensor(double fov, double mv);
    void Obs(base::Catalog& cat, base::Pointing& p);
    void Status();
    base::L1 l1;
    base::L2 l2;
private:
    double fov;
    double mv;
    base::Pointing pointing;
};

}

#endif // SENSOR_H
