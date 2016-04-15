#include "sensor.h"

sensor::Sensor::Sensor() {};
sensor::Sensor::Sensor(geometry::UnitVector& pointing, double yaw, double fovradius=4.0*geometry::pi/180.0)
    : pointing(pointing),
      yaw(yaw),
      fovradius(fovradius),
      attitude(pointing, yaw)
{
}

sensor::Obs sensor::Sensor::GetObs(catalog::Catalog& cat)
{
    sensor::Obs obs;
    obs.pointing = pointing;
    obs.yaw = yaw;
    obs.attitude = attitude;

    std::vector<int> ndxs = cat.StarsNearPoint(pointing, fovradius);
    obs.uv.set_size(ndxs.size(),3);
    obs.tpc.set_size(ndxs.size(),2);
    for (uint i = 0; i < ndxs.size(); ++i) {
        obs.ndxs.push_back(ndxs[i]);
        obs.mag.push_back(cat.stars[i].mv1);
        obs.uv.row(i) = trans(cat.stars[i].uvec.uv);
    }
    obs.uv = trans(geometry::q2rm(obs.attitude.q) * trans(obs.uv));
    obs.tpc.col(0) = obs.uv.col(0) / obs.uv.col(2);
    obs.tpc.col(0) = obs.uv.col(1) / obs.uv.col(2);

    return obs;
}
