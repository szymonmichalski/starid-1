#include "sensor.h"

sensor::Sensor::Sensor(util::UnitVector &pointing, double yaw, double fovradiusin) {
    util::Quaternion q(pointing, yaw);
    attitude = q;
    fovradius = fovradiusin;
}

sensor::Obs sensor::Sensor::GetObs() {
    sensor::Obs obs;
    obs.attitude = attitude;
    return obs;
}
