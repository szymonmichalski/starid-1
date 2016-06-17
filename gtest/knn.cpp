#include "../base/pointing.h"
#include "../base/catalog.h"
#include "../base/sensor.h"
#include "../knn/knntrain.h"

#include <armadillo>
#include "gtest/gtest.h"

TEST(knn, test1)
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
        sensor.Click(catalog, p);
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

TEST(knn, test2)
{
    arma::arma_rng::set_seed_random();

    using namespace arma;
    std::string fcatalog = "../../SKYMAP_SKY2000_V5R4.txt";
    double t = 0.0;
    double mv = 6.5;
    double fov = 4.0 * datum::pi / 180.0;
    base::Catalog catalog(fcatalog, t, mv);
    base::Sensor sensor(fov, mv);

    uint catndx1 = 4030;
    std::string star_name = catalog.stars[catndx1].star_name;
    double ra = catalog.stars[catndx1].ra;
    double dec = catalog.stars[catndx1].dec;
    double yaw = 0.0 * arma::datum::pi / 180.0;
    base::Pointing p(ra, dec, yaw);
    sensor.Click(catalog, p);
    vec fv = sensor.l2a.fv;

    knn::KnnTrain knntrain(catalog, sensor);
//    knntrain.StatusFeatures();
//    simple.StatusOrthogonality();
    uint catndx2 = knntrain.Classify(fv);

    EXPECT_EQ(catndx1, catndx2);

}
