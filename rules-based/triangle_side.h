/// **triangle side**
///
/// for adding, finding, removing, etc star pairs to a triangle side. one objective here is to work with maps of unique star keys, one key per star, rather than maps with multiple keys per star. this means using unordered_map, not unordered_multimap.
///
#ifndef TRIANGLE_SIDE_H
#define TRIANGLE_SIDE_H
#include <unordered_map>
#include <map>
#include "pairs_over_whole_sky.h"

namespace rules {

class TriangleSide {

public:

  /// *stars* each star is a map key whose value is a map of star keys it pairs with
  ///
  std::unordered_map<int, std::unordered_map<int, int>> stars;

  /// *refresh pairs* bring back pair information from an earlier side
  ///
  void refresh_pairs(TriangleSide &side);

  /// *prune pairs* remove pairs that have value zero or are no longer stars. then remove stars that have no pairs.
  ///
  void prune_pairs();

  /// *intersect stars* leave stars that are in both sides
  ///
  static void intersect_stars(TriangleSide &sidea, TriangleSide &sideb);

  std::vector<int> log_star_count;
  std::vector<int> log_pair_count;
  std::vector<bool> log_teststar;
  int teststar;
  bool hasteststar;

  TriangleSide(double ang, double tol_radius, rules::PairsOverWholeSky& pairs,
               int teststar);
  TriangleSide(int teststar);

  std::map<int, int> summary();
  bool has_teststar(int teststar);
  int pair_count();

private:

};

}

#endif // TRIANGLE_SIDE_H
