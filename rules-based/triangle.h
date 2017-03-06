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

  /// *link side1 and side3* travel around sides ab to bc to ca connecting by pairs.
  ///
  void close_loops(int maxits = 1);

  Triangle(double ang1, double ang2, double ang3,
           double tolerance,
           rules::PairsOverWholeSky& pairs,
           int teststar);

  Triangle(int teststar);

  rules::TriangleSide side1;
  rules::TriangleSide side2;
  rules::TriangleSide side3;
  std::vector<int> loops_star1;
  std::vector<int> loops_star2;
  std::vector<int> loops_star3;
  int teststar;

private:

};

}

#endif // TRIANGLE_H
