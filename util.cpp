#include "util.h"

util::UnitVector::UnitVector(double ra, double dec) {
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

void util::UnitVector::Xyz(double x, double y, double z) {
    double norm = sqrt(x*x + y*y + z*z);
    x = x/norm;
    y = y/norm;
    z = z/norm;
    assert (x >= -1.0 && x <= 1.0);
    assert (y >= -1.0 && y <= 1.0);
    assert (z >= -1.0 && z <= 1.0);
    assert ((sqrt(x*x + y*y + z*z) - 1.0) < 1e-10);
}

double util::UnitVector::Angle(UnitVector uvec2) {
    double angle = acos(x*uvec2.x + y*uvec2.y + z*uvec2.z);
    return angle;
}
