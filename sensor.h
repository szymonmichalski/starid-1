#ifndef SENSOR_H
#define SENSOR_H

#include "base.h"
#include "catalog.h"

namespace sensor {

struct Obs {
    base::UnitVector pointing;
    double yaw;
    base::Quaternion attitude;
    Col<int> ndxs;
    mat uv;
    vec mag;
};

class Sensor {
public:
    Sensor();
    Sensor(base::UnitVector& pointingin, double yawin, double fovradiusin);
    sensor::Obs GetObs(catalog::Catalog& cat);
private:
    double fovradius;
    double yaw;
    base::UnitVector pointing;
    base::Quaternion attitude;
    base::Quaternion q;
};

}

#endif // SENSOR_H
