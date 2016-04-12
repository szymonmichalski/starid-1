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
    Sensor(util::UnitVector& pointingin, double yawin, double fovradiusin);
    sensor::Obs GetObs(catalog::Catalog& cat);
private:
    double fovradius {4.0*util::pi/180.0};
    double yaw;
    util::UnitVector pointing;
    util::Quaternion attitude;
    util::Quaternion q;
};

}

#endif // SENSOR_H
