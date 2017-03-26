/// **star identifier**
///
/// find star triangles in the image, and candidate stars that meet the constraints implicit within the triangle. these constraints are effectively the rules for candidate stars. for example, if a triangle consists of star pairs ab and bc, then the third side is ac.
///
#ifndef STARIDENTIFIER_H
#define STARIDENTIFIER_H
#include "triangle.h"
#include "triangle_side.h"
#include "pairs.h"
#include "globals.h"
#include "image.h"
#include <eigen/Core>
#include <unordered_map>
#include <map>

namespace rules {

class StarIdentifier
{

public:

  StarIdentifier(stars::Image& image, stars::Pairs& pairs, double tolerance);

  /// *identify central star* this is the main function
  ///
  int identifyCentralStar(int teststar);

private:

  bool get_angs_c();
  bool get_angs_d();
  stars::Pairs pairs;
  stars::Image& image;
  double tolerance;
  double min_ang;
  std::vector<double> angs_c;
  std::vector<double> angs_d;
  arma::vec uveca;
  arma::vec uvecb;
  arma::vec uvecc;
  arma::vec uvecd;
  int ndxb, ndxc, ndxd;
  int teststar;

};

}

#endif
