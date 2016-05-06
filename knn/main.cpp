#include "../base/pointing.h"
#include "../base/catalog.h"
#include "../base/sensor.h"

#include <armadillo>

int main()
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
        sensor.Obs(catalog, p);
        fvs1.col(i) = sensor.l2.fv1;
        fvs2.col(i) = sensor.l2.fv2;
    }

    rowvec nfeatures1 = sum(fvs1);
    mat dot1 = trans(normalise(fvs1)) * normalise(fvs1);

    rowvec nfeatures2 = sum(fvs2);
    mat dot2 = trans(normalise(fvs2)) * normalise(fvs2);

    std::cout << hist(nfeatures1, linspace<vec>(0,60,10)) << "\n";
    std::cout << hist(nfeatures2, linspace<vec>(0,60,10)) << "\n";

    rowvec dot1rowvec = vectorise(dot1,1);
    rowvec dot2rowvec = vectorise(dot2,1);
    std::cout << hist(dot1rowvec, linspace<vec>(0,1,10))/2 << "\n";
    std::cout << hist(dot2rowvec, linspace<vec>(0,1,10))/2 << "\n";

    return 0;
}
