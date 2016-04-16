#include "sensor.h"

sensor::Obs::Obs() {
}

sensor::Sensor::Sensor(geometry::Pointing& pointing, double fovradius=4.0*datum::pi/180.0)
    : pointing(pointing),
      fovradius(fovradius)
{
}

sensor::Obs sensor::Sensor::GetObs(catalog::Catalog& cat)
{
    sensor::Obs obs;
    obs.fovradius = fovradius;
    obs.pointing = pointing;

    std::vector<int> ndxs = cat.StarsNearPoint(pointing.uv, fovradius);
    obs.uv.set_size(ndxs.size(),3);
    obs.tpc.set_size(ndxs.size(),2);
    for (uint i = 0; i < ndxs.size(); ++i) {
        obs.ndxs.push_back(ndxs[i]);
        obs.mag.push_back(cat.stars[ndxs[i]].mv1);
        obs.uv.row(i) = trans(cat.stars[ndxs[i]].uv);
    }
    obs.uv = trans(trans(pointing.RotationMatrix()) * trans(obs.uv));
    obs.tpc.col(0) = obs.uv.col(0) / obs.uv.col(2);
    obs.tpc.col(1) = obs.uv.col(1) / obs.uv.col(2);

    return obs;
}
