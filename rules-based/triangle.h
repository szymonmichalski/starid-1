/// **triangle**
///
/// represents a triangle as three constrained sides ab, bc, ca. travel around the sides ab to bc to ca so star pairs are not duplicated. if you turn around and travel ac to cb to ba, you get the same pairs backwards.
///
#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "triangle_side.h"

namespace rules {

class Triangle
{
public:

    Triangle(double angab, double angbc, double angca,
             double tol_radius, rules::PairsOverWholeSky& pairs);

    rules::TriangleSide ab;
    rules::TriangleSide bc;
    rules::TriangleSide ca;

};

}

#endif // TRIANGLE_H
