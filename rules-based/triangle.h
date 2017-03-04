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
  void link_side1_and_side3();

  /// *link abda and adca* link the shared ad side of abda and adca triangles
  ///
  static void link_abda_and_adca(Triangle &abda, Triangle &adca);

  Triangle(double ang1, double ang2, double ang3,
           double tol_radius,
           rules::PairsOverWholeSky& pairs,
           int teststar);
  Triangle(int teststar);

  rules::TriangleSide side1;
  rules::TriangleSide side2;
  rules::TriangleSide side3;
  std::vector<int> star1;
  std::vector<int> star2;
  std::vector<int> star3;
  int teststar;

  void update_side1(TriangleSide &side1new);
  void update_side3(TriangleSide &side3new);

private:

};

}

#endif // TRIANGLE_H
