#include "globals.h"

double starid::image_radius_radians  = 0.0698131700797732; // four degrees in radians
double starid::star_pair_angle_limit = 0.197461463918150; // 2*sqrt(2)*image_radius_radians
double starid::image_radius_unit_vector_plane = 0.0697564737441253; // sin(4*pi/180)
double starid::image_pixel_unit_vector_plane = 0.00498260526743752; // sin(4*pi/180)/14
double starid::star_brightness_limit = 6.5; // star visual magnitude
double starid::pi = 3.14159265358979323846;
double starid::arcseconds_to_radians = starid::pi / 648000.0;

starid::stopwatch::stopwatch() {
    t1 = std::chrono::steady_clock::now();
}

int starid::stopwatch::end() {
    t2= std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
}

void starid::stopwatch::reset() {
    t1 = std::chrono::steady_clock::now();
}
