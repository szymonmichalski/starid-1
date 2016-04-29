#include "sensor.h"

base::Obs::Obs(double fovradius, double mv)
    : fovradius(fovradius), mv(mv) {
    uv.zeros(1,3);
    tpc.zeros(1,2);
    features.zeros(10,10);
}

base::Sensor::Sensor(double fovradius, double mv)
    : fov(fovradius), mv(mv) {
}

void base::Sensor::SetPointing(base::Pointing& pointing0) {
    pointing = pointing0;
}

base::Obs base::Sensor::GetObs(base::Catalog& cat) {
    base::Obs obs(fov, mv);
    std::vector<int> ndxs = cat.StarsNearPoint(pointing.uv, fov);
    obs.uv.set_size(ndxs.size(),3);
    obs.tpc.set_size(ndxs.size(),2);
    for (uint i = 0; i < ndxs.size(); ++i) {
        obs.ndxs.push_back(ndxs[i]);
        obs.mag.push_back(cat.stars[ndxs[i]].mv1);
        obs.uv.row(i) = trans(cat.stars[ndxs[i]].uv);
    }
    obs.uv = trans(trans(pointing.RotationMatrix()) * trans(obs.uv));
    obs.tpc.col(0) = arma::atan(obs.uv.col(0) / obs.uv.col(2));
    obs.tpc.col(1) = arma::atan(obs.uv.col(1) / obs.uv.col(2));

    // features matrix, convert tpc to
    std::vector<int> xvec, yvec;
    for (uint i = 0; i < ndxs.size(); ++i) {
        int x, y;
        if (obs.tpc(i,0) == 0 || obs.tpc(i,1) == 0) continue;
        double xfac = obs.tpc(i,0) / fov;
        if (obs.tpc(i,0) > 0) {
            x = 4 + ceil(5 * xfac);
        } else {
            x = 5 + floor(5 * xfac);
        }
        double yfac = obs.tpc(i,1) / fov;
        if (obs.tpc(i,1) > 0) {
            y = 4 + ceil(5 * yfac);
        } else {
            y = 5 + floor(5 * yfac);
        }
        obs.features(x,y) = 1.0;
        xvec.push_back(x);
        yvec.push_back(y);
    }

    return obs;
}

void base::Obs::Status() {
    std::cout << uv << "\n";
    std::cout << tpc << "\n";
    std::cout << features << "\n";
}
