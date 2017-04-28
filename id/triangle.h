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

namespace id {

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
             stars::Pairs& pairs,
             int teststar,
             Eigen::Vector3d vecstar3);

    id::TriangleSide side1;
    id::TriangleSide side2;
    id::TriangleSide side3;
    int loops_cnt;
    int teststar;
    double tolerance;
    stars::Pairs &pairs;
    Eigen::Vector3d vecstar3;

private:

};

}

#endif // TRIANGLE_H