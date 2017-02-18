/// **triangle**
///
/// represents a triangle as three constrained sides ab, bc, ca. travel around the sides ab to bc to ca so star pairs are not duplicated. traveling ac to cb to ba, you get the same pairs backwards.
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

    /// *prune* travel around ab to bc to ca pruning the pairs maps. at the end, prune empty stars from the sides.
    ///
    void prune();

    /// *fourth star* use the additional information from a fourth star to further constrain the triangle sides. directly reduce sides ab and ca, then prune the triangle;
    ///
    void fourth_star(double angda, double angdb, double angdc);

};

}

#endif // TRIANGLE_H
