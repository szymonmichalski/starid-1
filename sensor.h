#ifndef SENSOR_H
#define SENSOR_H

#include "util.h"

namespace sensor {

class Sensor {
public:
    Sensor(util::UnitVector &pointing, double yaw);
private:
    util::Quaternion attitude;
};

}

#endif // SENSOR_H
