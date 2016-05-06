#include "../base/pointing.h"
#include "../base/catalog.h"
#include "../base/sensor.h"

#include <armadillo>

int main()
{
    std::string fcatalog = "../../SKYMAP_SKY2000_V5R4.txt";
    double t = 0.0;
    double mv = 6.5;
    double fov = 4.0 * arma::datum::pi / 180.0;
    base::Catalog catalog(fcatalog, t, mv);
    base::Sensor sensor(fov, mv);

    std::vector<arma::Col<int>> fvs1;
    std::vector<arma::Col<int>> fvs2;
    for (base::Star star : catalog.stars) {
        base::Pointing p(star.ra, star.dec, 0.0);
        sensor.Obs(catalog, p);
        fvs1.push_back(sensor.l2.fv1);
        fvs2.push_back(sensor.l2.fv2);
    }

    return 0;
}
