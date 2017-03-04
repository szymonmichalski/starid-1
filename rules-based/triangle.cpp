#include "triangle.h"

rules::Triangle::Triangle(double ang1, double ang2, double ang3,
                          double tol_radius, rules::PairsOverWholeSky& pairs,
                          int teststar)
  : side1(ang1, tol_radius, pairs, teststar),
    side2(ang2, tol_radius, pairs, teststar),
    side3(ang3, tol_radius, pairs, teststar),
    teststar(teststar) {
  link_side1_and_side3();
}

rules::Triangle::Triangle(int teststar)
  : side1(teststar),
    side2(teststar),
    side3(teststar),
    teststar(teststar) {
}

void rules::Triangle::link_side1_and_side3() {
  star1.clear();
  star2.clear();
  star3.clear();
  int maxits = 10;
  for (int it = 0; it < maxits; ++it) {
    TriangleSide::intersect_stars(side1, side3);
    for (auto it11 = side1.stars.begin(), end = side1.stars.end(); it11 != end; ++it11) {
      auto &pairs1 = it11->second;
      auto it13 = side3.stars.find(it11->first);
      auto &pairs3 = it13->second;

      for (auto it21 = pairs1.begin(), end = pairs1.end(); it21 != end; ++it21) {
        auto it22 = side2.stars.find(it21->first);
        if (it22 != side2.stars.end()) {
          auto &pairs2 = it22->second;

          for (auto it32 = pairs2.begin(), end = pairs2.end(); it32 != end; ++it32) {
            auto it33 = pairs3.find(it32->first); // backing into side 3...
            if (it33 != pairs3.end()) {
              ++it21->second;
              ++it32->second;
              ++it33->second;
              if (it == maxits-1) {
                star1.push_back(it11->first);
                star2.push_back(it21->first);
                star3.push_back(it32->first);
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



