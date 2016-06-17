#include "../base/pointing.h"
#include "../base/catalog.h"
#include "../base/sensor.h"
#include "svmtrain.h"
#include <armadillo>

int main()
{
    using namespace arma;
    arma::arma_rng::set_seed_random();

    std::string fcatalog = "../../SKYMAP_SKY2000_V5R4.txt";
    double t = 0.0;
    double mv = 6.5;
    double fov = 4.0 * datum::pi / 180.0;
    base::Catalog catalog(fcatalog, t, mv);
    base::Sensor sensor(fov, mv);

    uint catndx1 = 4030;
    double ra1 = catalog.stars[catndx1].ra;
    double dec1 = catalog.stars[catndx1].dec;
    double yaw1 = 0.0 * arma::datum::pi / 180.0;
    base::Pointing p1(ra1, dec1, yaw1);
    uint catndx2 = 4000;
    double ra2 = catalog.stars[catndx2].ra;
    double dec2 = catalog.stars[catndx2].dec;
    double yaw2 = 0.0 * arma::datum::pi / 180.0;
    base::Pointing p2(ra2, dec2, yaw2);


    mat examples(200, 100, fill::zeros) ;
    vec labels = zeros<vec>(200);
    for (uint i = 0; i < 100; ++i) {
        sensor.Click(catalog, p1);
        examples.row(i) = trans(sensor.l2b.fv);
        labels(i) = 1.0;
    }
    for (uint i = 100; i < 200; ++i) {
        sensor.Click(catalog, p2);
        examples.row(i) = trans(sensor.l2b.fv);
        labels(i) = -1.0;
    }

    svm::SvmTrain svmtrain(examples, labels);

    return 0;
}
