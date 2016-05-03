#ifndef SENSOR_H
#define SENSOR_H

#include "geometry.h"
#include "catalog.h"

namespace base {

struct L1 {
    L1(double fovradius, double mv);
    double fovradius;
    double mv;
    arma::mat uv; // n x 3, xyz
    arma::mat tpc; // n x 2, tangent plane coordinates in radians
    base::Pointing pointing;
    std::vector<int> ndxs;
    std::vector<double> mag;
    void Status();
};

struct L2 {
    L2(base::L1& l1);
    double fovradius;
    double mv;
    arma::Mat<int> n10;
    arma::Mat<int> n100;
};

class Sensor {
public:
    Sensor(double fov, double mv);
    double fov;
    double mv;
    base::Pointing pointing;
    void SetPointing(base::Pointing& pointing);
    base::L1 Level1(base::Catalog& cat);
    base::L2 Level2(base::L1& l1);
private:
};

}

#endif // SENSOR_H
