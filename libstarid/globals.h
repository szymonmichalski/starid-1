/// *globals*
///
/// global values
///

#ifndef GLOBALS_H
#define GLOBALS_H
#include <chrono>

namespace starid {

extern double image_radius_radians;
extern double image_radius_unit_vector_plane;
extern double image_pixel_unit_vector_plane;
extern double star_brightness_limit;
extern double star_pair_angle_limit;
extern double pi;
extern double arcseconds_to_radians;

class stopwatch {
public:
    std::chrono::steady_clock::time_point t1;
    std::chrono::steady_clock::time_point t2;
    stopwatch();
    int end();
    void reset();
};

}

#endif // GLOBALS_H
