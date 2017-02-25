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

    Triangle(double ang1, double ang2, double ang3,
             double tol_radius,
             rules::PairsOverWholeSky& pairs,
             int teststar);
    Triangle(int teststar);

    rules::TriangleSide side1;
    rules::TriangleSide side2;
    rules::TriangleSide side3;
    int teststar;

    /// *connect pairs* travel around sides ab to bc to ca connecting by pairs.
    ///
    void connect_pairs();

    /// *side2 side3* create side2 and side3 for an abda triangle
    ///
    void side2_side3(double ang2, double ang3,
               double tol_radius, rules::PairsOverWholeSky &pairs);

    /// *side1 side2* create side1 and side2 for an adca triangle
    ///
    void side1_side2(double ang1, double ang2,
               double tol_radius, rules::PairsOverWholeSky &pairs);

    void clean();
    void update13(TriangleSide &side1new, TriangleSide &side3new);
    void update1(TriangleSide &side1new);
    void update3(TriangleSide &side3new);

};

}

#endif // TRIANGLE_H
