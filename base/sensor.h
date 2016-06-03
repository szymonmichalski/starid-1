#ifndef SENSOR_H
#define SENSOR_H

#include "pointing.h"
#include "catalog.h"

namespace base {

struct L1 {
    arma::mat uv;
    arma::mat hv;
    std::vector<int> ndxs; // star catalog ndxs
    std::vector<double> mag; // star brightnesss
};

struct L2 {
    arma::Mat<double> pattern; // star pattern two dimensional matrix
    arma::Col<double> fv(); // star pattern as column vector
};

class Sensor {
public:
    Sensor(double fov, double mv, double noise=5.0,
           double false_stars_mean=1.0, double false_stars_var=1.0);

    base::L1 l1a; // ideal level 1
    base::L1 l1b; // more realistic level 1
    base::L2 l2a; // ideal level 2
    base::L2 l2b; // more realistic level 2
    void L1a(base::Catalog& cat, base::Pointing& p);
    void L1b();
    void L2a();
    void L2b();
    void Click(base::Catalog& cat, base::Pointing& p);

    void Status();

private:
    double fov; // fov radius, radians
    double mv; // dimmest star
    double noise; // pointing vector noise equivalent angle, arcseconds
    double false_stars_mean; // false star count per click mean
    double false_stars_var; // false star count per click var
    base::Pointing pointing;
};

}

#endif // SENSOR_H
