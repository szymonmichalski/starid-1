#include "sensor.h"

base::Sensor::Sensor(double fovradius, double mv)
    : fov(fovradius), mv(mv) {
}

void base::Sensor::Obs(base::Catalog& cat,  base::Pointing& p) {
    pointing = p;
    std::vector<int> ndxs = cat.StarsNearPoint(pointing.uv, fov);

    l1.uv.set_size(ndxs.size(),3);
    l1.hv.set_size(ndxs.size(),2);
    for (uint i = 0; i < ndxs.size(); ++i) {
        l1.ndxs.push_back(ndxs[i]);
        l1.mag.push_back(cat.stars[ndxs[i]].mv1);
        l1.uv.row(i) = trans(cat.stars[ndxs[i]].uv);
    }
    l1.uv = trans(trans(pointing.RotationMatrix()) * trans(l1.uv));
    l1.hv.col(0) = arma::atan(l1.uv.col(0) / l1.uv.col(2));
    l1.hv.col(1) = arma::atan(l1.uv.col(1) / l1.uv.col(2));

    l2.pat1.zeros(10,10);
    l2.pat2.zeros(100,100);
    for (uint i = 0; i < l1.ndxs.size(); ++i) {
        int h1 = 5 + floor(5 * l1.hv(i,0) / fov);
        int v1 = 5 + floor(5 * l1.hv(i,1) / fov);
        l2.pat1(h1,v1) = 1;
        int h2 = 50 + floor(50 * l1.hv(i,0) / fov);
        int v2 = 50 + floor(50 * l1.hv(i,1) / fov);
        l2.pat2(h2,v2) = 1;
    }

}

void base::Sensor::Status() {
    std::cout << l1.uv << "\n";
    std::cout << l1.hv << "\n";
    std::cout << l2.pat1 << "\n";
}

