#ifndef SENSOR_H
#define SENSOR_H

#include "geometry.h"
#include "catalog.h"

namespace sensor {

struct Obs {
    geometry::UnitVector pointing;
    double yaw;
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
    double fovradius;
    double yaw;
    geometry::UnitVector pointing;
private:
};

}

#endif // SENSOR_H
