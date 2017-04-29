/// *triangle*
///
/// represents a triangle as three constrained sides ab, bc, ca. travel around the sides ab to bc to ca so star pairs are not duplicated. traveling ac to cb to ba, you get the same pairs backwards.
///
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "triangle_side.h"
#include "sky.h"
#include "pairs.h"
#include <Eigen/Core>

namespace starid {

class Triangle
{

public:

    /// *close loops abca* travel around sides connecting by pairs.
    ///
    void close_loops_abca();

    /// *close loops abda* travel around sides connecting by pairs.
    ///
    void close_loops_abda(std::vector<Triangle> &triangles);

    Triangle(double ang1,
             double ang2,
             double ang3,
             double tolerance,
             starid::Pairs& pairs,
             int teststar,
             Eigen::Vector3d vecstar3);

    starid::TriangleSide side1;
    starid::TriangleSide side2;
    starid::TriangleSide side3;
    int loops_cnt;
    int teststar;
    double tolerance;
    starid::Pairs &pairs;
    Eigen::Vector3d vecstar3;

private:

};

}

#endif // TRIANGLE_H
