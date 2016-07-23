#include "sensor.h"

stars::Sensor::Sensor(double fov, double mv, double noise,
                     double false_stars_mean, double false_stars_var)
    : fov(fov), mv(mv), noise(noise),
      false_stars_mean(false_stars_mean), false_stars_stdv(false_stars_var)
{
}

void stars::Sensor::L1a(stars::Catalog& cat,  stars::Pointing& p) {
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

void stars::Sensor::L1b() {
    using namespace arma;
    l1b.ndxs = l1a.ndxs;
    l1b.mag = l1a.mag;

    mat hvnoise = (noise * datum::pi / 6.48e5) * randn(l1a.hv.n_rows, l1a.hv.n_cols);
    l1b.hv = l1a.hv + hvnoise;

    // handle false stars in hv space
    vec nfalsevec = false_stars_mean + (false_stars_stdv * arma::randn(1));
    int nfalse = std::round(nfalsevec(0));
    if (nfalse > 0) {
        uint ntrue = l1b.hv.n_rows;
        l1b.hv.resize(ntrue + nfalse, l1b.hv.n_cols);
        for (uint i = 1; i <= nfalse; ++i) {
            l1b.ndxs.push_back(-1);
            l1b.mag.push_back(-1.0);
            vec hvrand = ((randu(2) * 2.0) - 1.0) * fov;
            l1b.hv.row(ntrue - 1 + i) = trans(hvrand);
        }
    }

    // generate pointing vector from hv space
    mat z(l1b.hv.n_rows, 1, fill::ones);
    l1b.uv = l1b.hv;
    l1b.uv.insert_cols(2, z);
    normalise(l1b.uv, 2, 1);
}

void stars::Sensor::L2a() {
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

    l2a.pattern.zeros(28,28);
    for (uint i = 0; i <= hv2.n_rows-1; ++i) {
        try {
            int h1 = 14 + floor(14 * hv2(i,0) / fov);
            int v1 = 14 + floor(14 * hv2(i,1) / fov);
            l2a.pattern(h1,v1) = 1.0;
        } catch (...) {
            bool outofbounds = true;
        }
    }
    l2a.fv = arma::vectorise(l2a.pattern);
}

void stars::Sensor::L2b() {
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

    l2b.pattern.zeros(28,28);
    for (uint i = 0; i <= hv2.n_rows-1; ++i) {
        try {
            int h1 = 14 + floor(14 * hv2(i,0) / fov);
            int v1 = 14 + floor(14 * hv2(i,1) / fov);
            l2b.pattern(h1,v1) = 1.0;
        } catch (...) {
            bool outofbounds = true;
        }
    }
    l2b.fv = arma::vectorise(l2b.pattern);
}

void stars::Sensor::Click(stars::Catalog& cat, stars::Pointing& p) {
    L1a(cat, p);
    L1b();
    L2a();
//    L2b();
}

void stars::Sensor::Status() {
//    std::cout << l1a.uv << "\n";
//    std::cout << l1a.hv << "\n";
    std::cout << l2a.pattern << "\n";
}

