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
           rules::PairsOverWholeSky& pairs,
           int teststar,
           arma::vec avecstar3);

  rules::TriangleSide side1;
  rules::TriangleSide side2;
  rules::TriangleSide side3;
  int loops_cnt;
  int teststar;
  double tolerance;
  rules::PairsOverWholeSky &pairs;
  arma::vec avecstar3;
  Eigen::Vector3d evecstar3;

private:

};

}

#endif // TRIANGLE_H
