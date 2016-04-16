#ifndef SENSOR_H
#define SENSOR_H

#include "geometry.h"
#include "catalog.h"

namespace sensor {

struct Obs {
    Obs();
    double fovradius;
    geometry::Pointing pointing;
    std::vector<int> ndxs;
    std::vector<double> mag;
    mat uv; // n x 3, xyz
    mat tpc; // n x 2, tangent plane coordinates
};

class Sensor {
public:
    Sensor(geometry::Pointing& pointing, double fovradius);
    sensor::Obs GetObs(catalog::Catalog& cat);
    double fovradius;
    geometry::Pointing pointing;
private:
};

}

#endif // SENSOR_H
