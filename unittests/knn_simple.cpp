#include "../base/pointing.h"
#include "../base/catalog.h"
#include "../base/sensor.h"

#include <armadillo>
#include "gtest/gtest.h"

TEST(knn_simple, simple)
{
    using namespace arma;
    std::string fcatalog = "../../SKYMAP_SKY2000_V5R4.txt";
    double t = 0.0;
    double mv = 6.5;
    base::Catalog catalog(fcatalog, t, mv);

    double fov = 4.0 * datum::pi / 180.0;
    base::Sensor sensor(fov, mv);

    Mat<double> fvs;
    fvs.zeros(100, catalog.stars.size());
    for (uint i = 0; i <= catalog.stars.size()-1; ++i) {
        base::Pointing p(catalog.stars[i].ra, catalog.stars[i].dec, 0.0);
        sensor.L1a(catalog, p);
        sensor.L2a();
        fvs.col(i) = sensor.l2a.fv;
    }

    rowvec nfeatures = sum(fvs);
    mat k = trans(normalise(fvs)) * normalise(fvs);

    urowvec histk = hist(nfeatures, linspace<vec>(0,60,10));
    EXPECT_GE(histk(0), 103);
    EXPECT_LE(histk(0), 104);

//    vec kvec = vectorise(k);
//    uvec histkvec = hist(kvec, linspace<vec>(0,1,10)) / 2;
//    histkvec(9) = histkvec(9) - 4439;
//    std::cout << trans(histkvec) << "\n";
}
