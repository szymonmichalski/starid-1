#include "triangle.h"

rules::Triangle::Triangle(double ang1, double ang2, double ang3,
                          double tol_radius, rules::PairsOverWholeSky& pairs,
                          int teststar)
  : side1(ang1, tol_radius, pairs, teststar),
    side2(ang2, tol_radius, pairs, teststar),
    side3(ang3, tol_radius, pairs, teststar),
    teststar(teststar) {
}

rules::Triangle::Triangle(int teststar)
  : side1(teststar),
    side2(teststar),
    side3(teststar),
    teststar(teststar) {
}

void rules::Triangle::close_loops(int maxits) {
  loops_star1.clear();
  loops_star2.clear();
  loops_star3.clear();
  for (int it = 0; it < maxits; ++it) {

    for (auto it11 = side1.stars.begin(), end = side1.stars.end(); it11 != end; ++it11) {
      auto &pairs1 = it11->second;

      int star1side1 = it11->first;                     // star1 side1
      auto star1side3 = side3.stars.find(star1side1);   // star1 side3
      if (star1side3 == side3.stars.end()) continue;
      auto &pairs3 = star1side3->second;

      for (auto pairs1it = pairs1.begin(), end = pairs1.end(); pairs1it != end; ++pairs1it) {

        int star2side1 = pairs1it->first;               // star2 side1
        auto star2side2 = side2.stars.find(star2side1); // star2 side2
        if (star2side2 == side2.stars.end()) continue;
        auto &pairs2 = star2side2->second;

        for (auto pairs2it = pairs2.begin(), end = pairs2.end(); pairs2it != end; ++pairs2it) {

          int star3side2 = pairs2it->first;             // star3 side2
          auto star3side3 = pairs3.find(star3side2);    // star3 side3
          if (star3side3 == pairs3.end()) continue;

          pairs1it->second = 1;
          pairs2it->second = 1;
          star3side3->second = 1;
          if (it == maxits-1) {
            loops_star1.push_back(star1side1);
            loops_star2.push_back(star2side1);
            loops_star3.push_back(star3side2);
          }
        }
      }
    }
    side1.prune_pairs();
    side2.prune_pairs();
    side3.prune_pairs();
  }
}

void rules::Triangle::link_abda_and_adca(Triangle &abda, Triangle &adca) {
  TriangleSide::intersect_stars(abda.side3, adca.side1);
  abda.close_loops();
  adca.close_loops();
}


void rules::Triangle::update_side1(TriangleSide &side1new) {
  for (auto it1 = side1.stars.begin(); it1 != side1.stars.end(); ) {
    auto it1new = side1new.stars.find(it1->first);
    if (it1new == side1new.stars.end())
      it1 = side1.stars.erase(it1);
    else
      ++it1;
  }
}

void rules::Triangle::update_side3(TriangleSide &side3new) {
  for (auto it3 = side3.stars.begin(); it3 != side3.stars.end(); ) {
    auto it3new = side3new.stars.find(it3->first);
    if (it3new == side3new.stars.end())
      it3 = side3.stars.erase(it3);
    else
      ++it3;
  }
}



