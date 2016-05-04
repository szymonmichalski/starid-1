#include "sensor.h"

base::Sensor::Sensor(double fovradius, double mv)
    : fov(fovradius), mv(mv) {
}

void base::Sensor::Update(base::Catalog& cat,  base::Pointing& p) {
    pointing = p;
    std::vector<int> ndxs = cat.StarsNearPoint(pointing.uv, fov);
    l1.uv.set_size(ndxs.size(),3);
    l1.tpc.set_size(ndxs.size(),2);
    for (uint i = 0; i < ndxs.size(); ++i) {
        l1.ndxs.push_back(ndxs[i]);
        l1.mag.push_back(cat.stars[ndxs[i]].mv1);
        l1.uv.row(i) = trans(cat.stars[ndxs[i]].uv);
    }
    l1.uv = trans(trans(pointing.RotationMatrix()) * trans(l1.uv));
    l1.tpc.col(0) = arma::atan(l1.uv.col(0) / l1.uv.col(2));
    l1.tpc.col(1) = arma::atan(l1.uv.col(1) / l1.uv.col(2));

    for (uint i = 0; i < l1.ndxs.size(); ++i) {
        int h, v;
        if (l1.tpc(i,0) == 0.0 || l1.tpc(i,1) == 0.0) continue;
        double hfac = l1.tpc(i,0) / fov;
        if (hfac > 0) {
            h = 4 + ceil(5 * hfac); // 4 + (1,2,3,4,5)
        } else {
            h = 5 + floor(5 * hfac); // 5 + (-1,-2,-3,-4,-5)
        }
        double vfac = l1.tpc(i,1) / fov;
        if (vfac > 0) {
            v = 4 + ceil(5 * vfac); // 4 + (1,2,3,4,5)
        } else {
            v = 5 + floor(5 * vfac); // 5 + (-1,-2,-3,-4,-5)
        }
        l2.n10(h,v) = 1;
    }
}

void base::Sensor::Status() {
    std::cout << l1.uv << "\n";
    std::cout << l1.tpc << "\n";
    std::cout << l2.n10 << "\n";
}

