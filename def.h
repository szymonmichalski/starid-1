#ifndef DEF_H
#define DEF_H

#include <cmath>
#include <cassert>

constexpr double pi = 3.141592653589793238463;
constexpr double kUnixTimeToJ2000Offset = 946684800.0;

namespace Def
{
    struct UnitVector {
        double x;
        double y;
        double z;

        UnitVector() {
            x = 0.0;
            y = 0.0;
            z = 0.0;
        }
        UnitVector(double ra=0.0, double dec=0.0) {
            x = (cos(ra)*cos(dec));
            y = (sin(ra)*cos(dec));
            z = (sin(dec));
            double norm = sqrt(x*x + y*y + z*z);
            x = x/norm;
            y = y/norm;
            z = z/norm;
            assert (x >= -1.0 && x <= 1.0);
            assert (y >= -1.0 && y <= 1.0);
            assert (z >= -1.0 && z <= 1.0);
            norm = sqrt(x*x + y*y + z*z);
//            assert (norm == 1.0);
        }
    };
}
#endif
