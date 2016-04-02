#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <cassert>

namespace util {
    constexpr double pi = 3.141592653589793238463;
    constexpr double kUnixTimeToJ2000Offset = 946684800.0;
    constexpr double kRaOrion = 75.0*pi/180.0;
    constexpr double kDecOrion = 0.0*pi/180.0;
    constexpr double kRaCass = 0.0*pi/180.0;
    constexpr double kDecCass = 60.0*pi/180.0;


    struct UnitVector {
        double x {0.0};
        double y {0.0};
        double z {0.0};
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
            assert ((sqrt(x*x + y*y + z*z) - 1.0) < 1e-10);
        }
        void xyz(double x=0.0, double y=0.0, double z=0.0) {
            double norm = sqrt(x*x + y*y + z*z);
            x = x/norm;
            y = y/norm;
            z = z/norm;
            assert (x >= -1.0 && x <= 1.0);
            assert (y >= -1.0 && y <= 1.0);
            assert (z >= -1.0 && z <= 1.0);
            assert ((sqrt(x*x + y*y + z*z) - 1.0) < 1e-10);
        }
    };

}
#endif
