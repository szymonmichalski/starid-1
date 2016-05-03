#include "sensor.h"

base::L1::L1(double fovradius, double mv)
    : fovradius(fovradius), mv(mv) {
    uv.zeros(1,3);
    tpc.zeros(1,2);
    //    features.zeros(10,10);
}

base::L2::L2(base::L1& l1)
    : fovradius(l1.fovradius), mv(l1.mv) {
    n10.zeros(10,10);
    n100.zeros(100,100);
}

base::Sensor::Sensor(double fovradius, double mv)
    : fov(fovradius), mv(mv) {
}

void base::Sensor::SetPointing(base::Pointing& pointing0) {
    pointing = pointing0;
}

base::L1 base::Sensor::Level1(base::Catalog& cat) {
    base::L1 l1(fov, mv);
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
    return l1;
}

base::L2 base::Sensor::Level2(base::L1& l1) {
    base::L2 l2(l1);
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
    return l2;
}

void base::L1::Status() {
    std::cout << uv << "\n";
    std::cout << tpc << "\n";
    //    std::cout << features << "\n";
}
