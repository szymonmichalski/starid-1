#ifndef SENSOR_H
#define SENSOR_H

#include "util.h"

namespace sensor {

class Sensor {
public:

private:
    util::UnitVector pointing;
    double yaw {0.0};
    util::Quaternion attitude;
};

}

#endif // SENSOR_H
