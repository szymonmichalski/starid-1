#include "../base/pointing.h"
#include "../base/catalog.h"
#include "../base/sensor.h"

#include <armadillo>
#include "gtest/gtest.h"

TEST(knn_main, l2)
{
    using namespace arma;
    std::string fcatalog = "../../SKYMAP_SKY2000_V5R4.txt";
    double t = 0.0;
    double mv = 6.5;
    double fov = 4.0 * datum::pi / 180.0;
    base::Catalog catalog(fcatalog, t, mv);
    base::Sensor sensor(fov, mv);

    Mat<double> fvs1;
    Mat<double> fvs2;
    fvs1.zeros(1e2, catalog.stars.size());
    fvs2.zeros(1e4, catalog.stars.size());
    for (uint i = 0; i <= catalog.stars.size()-1; ++i) {
        base::Pointing p(catalog.stars[i].ra, catalog.stars[i].dec, 0.0);
        sensor.L1a(catalog, p);
        fvs1.col(i) = sensor.l2.fv1;
        fvs2.col(i) = sensor.l2.fv2;
    }

    rowvec nfeatures1 = sum(fvs1);
    mat dot1 = trans(normalise(fvs1)) * normalise(fvs1);

//    rowvec nfeatures2 = sum(fvs2);
//    mat dot2 = trans(normalise(fvs2)) * normalise(fvs2);

    urowvec hist1 = hist(nfeatures1, linspace<vec>(0,60,10));
//    urowvec hist2 = hist(nfeatures2, linspace<vec>(0,60,10));
//    std::cout << hist1 << "\n";
//    std::cout << hist2 << "\n";
    EXPECT_GE(hist1(0), 103);
    EXPECT_LE(hist1(0), 104);

//    vec dot1vec = vectorise(dot1);
//    vec dot2vec = vectorise(dot2);
//    uvec hist1 = hist(dot1vec, linspace<vec>(0,1,10))/2; hist1(9) = hist1(9) - 4439;
//    uvec hist2 = hist(dot2vec, linspace<vec>(0,1,10))/2; hist2(9) = hist2(9) - 4439;
//    std::cout << trans(hist1) << "\n";
//    std::cout << trans(hist2) << "\n";
}
