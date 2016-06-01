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
    arma::Mat<double> pat;
    arma::Col<double> fv;
};

class Sensor {
public:
    Sensor(double fov, double mv);

    base::L1 l1a;
    base::L1 l1b;
    base::L2 l2a;
    base::L2 l2b;
    void L1a(base::Catalog& cat, base::Pointing& p);
    void L1b();
    void L2a();
    void L2b();
    void Click(base::Catalog& cat, base::Pointing& p);

    void Status();

private:
    double fov;
    double mv;
    base::Pointing pointing;
};

}

#endif // SENSOR_H
