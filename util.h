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
        UnitVector(double ra=0.0, double dec=0.0);
        void Xyz(double x=0.0, double y=0.0, double z=0.0);
        double Angle(UnitVector uvec2);
    };

    struct Quaternion {
        double q1 {1.0};
        double q2 {0.0};
        double q3 {0.0};
        double q4 {0.0};
    };

}
#endif
