#ifndef SENSOR_H
#define SENSOR_H

#include "geometry.h"
#include "catalog.h"

namespace base {

struct Obs {
    Obs();
    double fovradius;
    base::Pointing pointing;
    std::vector<int> ndxs;
    std::vector<double> mag;
    mat uv; // n x 3, xyz
    mat tpc; // n x 2, tangent plane coordinates
};

class Sensor {
public:
    base::Pointing pointing;
    double fovradius;
    Sensor(base::Pointing& pointing, double fovradius);
    base::Obs GetObs(base::Catalog& cat);
private:
};

}

#endif // SENSOR_H
