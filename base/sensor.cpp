#include "sensor.h"

base::Obs::Obs() {
}

base::Sensor::Sensor(base::Pointing& pointing0, double fovradius0=4.0*arma::datum::pi/180.0)
    : pointing(pointing0),
      fovradius(fovradius0)
{
}

base::Obs base::Sensor::GetObs(base::Catalog& cat)
{
    base::Obs obs;
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
