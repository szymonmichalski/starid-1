#include "sensor.h"
#include "catalog.h"

sensor::Sensor::Sensor(util::UnitVector& pointingin, double yawin, double fovradiusin)
    : pointing(pointingin),
      yaw(yawin),
      fovradius(fovradiusin),
      q(pointingin, yawin)
{
}

sensor::Obs sensor::Sensor::GetObs(catalog::Catalog& cat)
{
    sensor::Obs obs;
    obs.pointing = pointing;
    obs.yaw = yaw;
    obs.attitude = attitude;

    std::vector<int> ndxs = cat.StarsNearPoint(pointing, fovradius);
    obs.ndxs.set_size(ndxs.size());
    obs.uv.set_size(ndxs.size(),3);
    obs.mag.set_size(ndxs.size());
    for (uint i = 0; i < ndxs.size(); ++i) {
        obs.ndxs(i) = ndxs[i];
        obs.uv.row(0) = cat.stars[i].uvec.uv.t();
        obs.mag(i) = cat.stars[i].mv1;
    }

    return obs;
}
