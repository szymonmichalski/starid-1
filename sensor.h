#ifndef SENSOR_H
#define SENSOR_H

#include "util.h"

namespace sensor {

struct Obs {
    util::Quaternion attitude;
};

class Sensor {
public:
    Sensor(util::UnitVector &pointing, double yaw, double fovradiusin);
    sensor::Obs GetObs();
private:
    util::Quaternion attitude;
    double fovradius {4.0*util::pi/180.0};
};

}

#endif // SENSOR_H
