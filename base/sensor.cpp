#include "sensor.h"

base::Sensor::Sensor(double fov, double mv, double noise, double falsestars)
    : fov(fov), mv(mv), noise(noise), falsestars(falsestars) {
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
    using namespace arma;

    mat hvnoise = (noise * datum::pi / 6.48e5) * randn(l1a.hv.n_rows, l1a.hv.n_cols);
    l1b.hv = l1a.hv + hvnoise;

    mat z(l1b.hv.n_rows, 1, fill::ones);
    l1b.uv = l1b.hv;
    l1b.uv.insert_cols(2, z);
    normalise(l1b.uv, 2, 1);
}

void base::Sensor::L2a() {
    using namespace arma;

    // rotate so the nearest star is on the v axis
    vec d = arma::sqrt(l1a.hv.col(0)%l1a.hv.col(0) + l1a.hv.col(1)%l1a.hv.col(1));
    uvec ndxs2 = arma::sort_index(d);
    double h = l1a.hv(ndxs2(0),0);
    double v = l1a.hv(ndxs2(0),1);
    double a = std::atan2(h,v); // angle from v axis
    mat hv2 = l1a.hv;
    mat rm = { {cos(a), -sin(a)}, {sin(a), cos(a)} };
    hv2 = trans(rm * trans(hv2));

    l2a.pattern.zeros(10,10);
    for (uint i = 0; i <= hv2.n_rows-1; ++i) {
        try {
            int h1 = 5 + floor(5 * hv2(i,0) / fov);
            int v1 = 5 + floor(5 * hv2(i,1) / fov);
            l2a.pattern(h1,v1) = 1.0;
        } catch (...) {
            bool outofbounds = true;
        }
    }
}

void base::Sensor::L2b() {
    using namespace arma;

    // rotate so the nearest star is on the v axis
    vec d = arma::sqrt(l1b.hv.col(0)%l1b.hv.col(0) + l1b.hv.col(1)%l1b.hv.col(1));
    uvec ndxs2 = arma::sort_index(d);
    double h = l1b.hv(ndxs2(0),0);
    double v = l1b.hv(ndxs2(0),1);
    double a = std::atan2(h,v); // angle from v axis
    mat hv2 = l1b.hv;
    mat rm = { {cos(a), -sin(a)}, {sin(a), cos(a)} };
    hv2 = trans(rm * trans(hv2));

    l2b.pattern.zeros(10,10);
    for (uint i = 0; i <= hv2.n_rows-1; ++i) {
        try {
            int h1 = 5 + floor(5 * hv2(i,0) / fov);
            int v1 = 5 + floor(5 * hv2(i,1) / fov);
            l2b.pattern(h1,v1) = 1.0;
        } catch (...) {
            bool outofbounds = true;
        }
    }
}

arma::Col<double> base::L2::fv() {
    return arma::vectorise(pattern);
}

void base::Sensor::Click(base::Catalog& cat, base::Pointing& p) {
    L1a(cat, p);
    L1b();
    L2a();
    L2b();
}

void base::Sensor::Status() {
//    std::cout << l1a.uv << "\n";
//    std::cout << l1a.hv << "\n";
    std::cout << l2a.pattern << "\n";
}

