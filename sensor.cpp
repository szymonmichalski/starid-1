#include "sensor.h"

sensor::Sensor::Sensor(util::UnitVector &pointing, double yaw) {
    util::Quaternion q(pointing, yaw);
    attitude = q;
}

