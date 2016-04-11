#ifndef SENSOR_H
#define SENSOR_H

#include "util.h"
#include "catalog.h"

namespace sensor {

struct Obs {
    util::UnitVector pointing;
    double yaw;
    util::Quaternion attitude;
    Col<int> ndxs;
    mat uv;
    vec mag;
};

class Sensor {
public:
    Sensor(util::UnitVector &pointingin, double yawin, double fovradiusin);
    sensor::Obs GetObs(catalog::Catalog &cat);
private:
    util::UnitVector pointing;
    double yaw;
    util::Quaternion attitude;
    double fovradius {4.0*util::pi/180.0};
};

}

#endif // SENSOR_H
