#include "globals.h"

double stars::imageRadiusRadians = 0.0698131700797732; // four degrees in radians
double stars::imageRadiusUnitVectors = 0.0697564737441253; // sin(4*pi/180)
double stars::imagePixelUnitVectors = 0.00498260526743752; // sin(4*pi/180)/14
double stars::imageFaintnessLimit = 6.5; // star visual magnitude
double stars::maxStarPairAngle = 2.8284 * stars::imageRadiusRadians; // 2*sqrt(2)
