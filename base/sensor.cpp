#include "sensor.h"

base::Sensor::Sensor(double fovradius, double mv)
    : fov(fovradius), mv(mv) {
}

void base::Sensor::L1a(base::Catalog& cat,  base::Pointing& p) {
    pointing = p;
    std::vector<int> ndxs = cat.StarsNearPoint(pointing.uv, fov);

    l1a.uv.set_size(ndxs.size(),3);
    l1a.hv.set_size(ndxs.size(),2);
    for (uint i = 0; i < ndxs.size(); ++i) {
        l1a.ndxs.push_back(ndxs[i]);
        l1a.mag.push_back(cat.stars[ndxs[i]].mv1);
        l1a.uv.row(i) = trans(cat.stars[ndxs[i]].uv);
    }
    l1a.uv = trans(trans(pointing.RotationMatrix()) * trans(l1a.uv));
    l1a.hv.col(0) = arma::atan(l1a.uv.col(0) / l1a.uv.col(2));
    l1a.hv.col(1) = arma::atan(l1a.uv.col(1) / l1a.uv.col(2));
}

void base::Sensor::L1b() {
    double hvsig = 2.5 * arma::datum::pi / 6.48e5;
}

void base::Sensor::L2a() {
    // rotate so the nearest star is on the v axis
    arma::vec d = arma::sqrt(l1a.hv.col(0)%l1a.hv.col(0) + l1a.hv.col(1)%l1a.hv.col(1));
    arma::uvec ndxs2 = arma::sort_index(d);
    double h = l1a.hv(ndxs2(0),0);
    double v = l1a.hv(ndxs2(0),1);
    double a = std::atan2(h,v); // angle from v axis
    arma::mat hv2 = l1a.hv;
    arma::mat rm = { {cos(a), -sin(a)}, {sin(a), cos(a)} };
    hv2 = trans(rm * trans(hv2));

    l2a.pat.zeros(10,10);
    for (uint i = 0; i <= hv2.n_rows-1; ++i) {
        try {
            int h1 = 5 + floor(5 * hv2(i,0) / fov);
            int v1 = 5 + floor(5 * hv2(i,1) / fov);
            l2a.pat(h1,v1) = 1.0;
            l2a.fv = arma::vectorise(l2a.pat);
        } catch (...) {
            bool outofbounds = true;
        }
    }
}

void base::Sensor::L2b() {

}

void base::Sensor::Status() {
//    std::cout << l1.uv << "\n";
//    std::cout << l1.hv << "\n";
    std::cout << l2a.pat << "\n";
}

