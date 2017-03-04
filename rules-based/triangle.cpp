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

void rules::Triangle::link_side1_and_side3(int maxits) {
  star1.clear();
  star2.clear();
  star3.clear();
  for (int it = 0; it < maxits; ++it) {
    TriangleSide::intersect_stars(side1, side3);

    for (auto it11 = side1.stars.begin(), end = side1.stars.end(); it11 != end; ++it11) { // star1 side1
      auto &pairs1 = it11->second;
      auto it13 = side3.stars.find(it11->first);
      auto &pairs3 = it13->second;

      for (auto pairs1it = pairs1.begin(), end = pairs1.end(); pairs1it != end; ++pairs1it) { // star2 side1
        auto it22 = side2.stars.find(pairs1it->first); // star2 side2
        if (it22 != side2.stars.end()) {
          auto &pairs2 = it22->second;

          for (auto pairs2it = pairs2.begin(), end = pairs2.end(); pairs2it != end; ++pairs2it) { // star3 side2
            auto pairs3it = pairs3.find(pairs2it->first); // backing into side 3...
            if (pairs3it != pairs3.end()) {
              ++pairs1it->second;
              ++pairs2it->second;
              ++pairs3it->second;
              if (it == maxits-1) {
                star1.push_back(it11->first);
                star2.push_back(pairs1it->first);
                star3.push_back(pairs2it->first);
              }
            }
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
  abda.link_side1_and_side3();
  adca.link_side1_and_side3();
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



