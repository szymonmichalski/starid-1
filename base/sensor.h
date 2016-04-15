#ifndef SENSOR_H
#define SENSOR_H

#include "base.h"
#include "catalog.h"

namespace sensor {

struct Obs {
    base::UnitVector pointing;
    double yaw;
    base::Quaternion attitude;
    std::vector<int> ndxs;
    std::vector<double> mag;
    mat uv; // n x 3, xyz
    mat tpc; // n x 2, tangent plane coordinates
};

class Sensor {
public:
    Sensor();
    Sensor(base::UnitVector& pointing, double yaw, double fovradius);
    sensor::Obs GetObs(catalog::Catalog& cat);
    base::Quaternion attitude;
private:
    double fovradius;
    double yaw;
    base::UnitVector pointing;
};

}

#endif // SENSOR_H
