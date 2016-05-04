#ifndef SENSOR_H
#define SENSOR_H

#include "pointing.h"
#include "catalog.h"

namespace base {

struct L1 {
    arma::mat uv; // n x 3, xyz
    arma::mat tpc; // n x 2, tangent plane coordinates in radians
    std::vector<int> ndxs;
    std::vector<double> mag;
};

struct L2 {
    arma::Mat<int> n10;
    arma::Mat<int> n100;
};

class Sensor {
public:
    Sensor(double fov, double mv);
    void Update(base::Catalog& cat, base::Pointing& p);
    void Status();
private:
    double fov;
    double mv;
    base::Pointing pointing;
    base::L1 l1;
    base::L2 l2;
};

}

#endif // SENSOR_H
