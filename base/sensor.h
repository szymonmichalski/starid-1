#ifndef SENSOR_H
#define SENSOR_H

#include "geometry.h"
#include "catalog.h"

namespace base {

struct Obs {
    double fovradius;
    double mv;
    arma::mat uv; // n x 3, xyz
    arma::mat tpc; // n x 2, tangent plane coordinates in radians
    arma::Mat<int> features;
    base::Pointing pointing;
    std::vector<int> ndxs;
    std::vector<double> mag;
    Obs(double fovradius, double mv);
    void Status();
};

class Sensor {
public:
    double fov;
    double mv;
    base::Pointing pointing;
    Sensor(double fov, double mv);
    void SetPointing(base::Pointing& pointing);
    base::Obs GetObs(base::Catalog& cat);
private:
};

}

#endif // SENSOR_H
