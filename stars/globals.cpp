#include "globals.h"

double stars::image_radius_radians = 0.0698131700797732; // four degrees in radians

double stars::image_radius_unit_vector_plane = 0.0697564737441253; // sin(4*pi/180)

double stars::image_pixel_unit_vector_plane = 0.00498260526743752; // sin(4*pi/180)/14

double stars::star_brightness_limit = 6.5; // star visual magnitude

double stars::star_pair_angle_limit = 2.8284 * stars::image_radius_radians; // 2*sqrt(2)

double stars::pi = 3.14159265358979323846;

double stars::arcseconds_to_radians = stars::pi / 648000.0;
