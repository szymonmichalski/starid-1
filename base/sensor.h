#ifndef SENSOR_H
#define SENSOR_H

#include "geometry.h"
#include "catalog.h"

namespace sensor {

struct Obs {
    geometry::UnitVector pointing;
    double yaw;
    geometry::Quaternion attitude;
    std::vector<int> ndxs;
    std::vector<double> mag;
    mat uv; // n x 3, xyz
    mat tpc; // n x 2, tangent plane coordinates
};

class Sensor {
public:
    Sensor();
    Sensor(geometry::UnitVector& pointing, double yaw, double fovradius);
    sensor::Obs GetObs(catalog::Catalog& cat);
    geometry::Quaternion attitude;
private:
    double fovradius;
    double yaw;
    geometry::UnitVector pointing;
};

}

#endif // SENSOR_H
