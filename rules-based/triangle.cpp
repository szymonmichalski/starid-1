#include "triangle.h"

rules::Triangle::Triangle(double ang1, double ang2, double ang3,
                          double tol_radius, rules::PairsOverWholeSky& pairs,
                          int teststar)
    : side1(ang1, tol_radius, pairs, teststar),
    side2(ang2, tol_radius, pairs, teststar),
    side3(ang3, tol_radius, pairs, teststar),
    teststar(teststar) {
    link_sides();
}

rules::Triangle::Triangle(int teststar)
    : side1(teststar),
      side2(teststar),
      side3(teststar),
      teststar(teststar) {
}

void rules::Triangle::link_sides() {
    TriangleSide::intersect_stars(side1, side3);
    for (auto ita1 = side1.stars.begin(), end = side1.stars.end(); ita1 != end; ++ita1) {
        auto &pairs1 = ita1->second;
        auto ita3 = side3.stars.find(ita1->first);
        auto &pairs3 = ita3->second;

        for (auto itb1 = pairs1.begin(), end = pairs1.end(); itb1 != end; ++itb1) {
            auto itb2 = side2.stars.find(itb1->first);
            if (itb2 != side2.stars.end()) {
                auto &pairs2 = itb2->second;

                for (auto itc2 = pairs2.begin(), end = pairs2.end(); itc2 != end; ++itc2) {
                    auto itc3 = pairs3.find(itc2->first); // backing into side 3...
                    if (itc3 != pairs3.end()) {
                        ++itb1->second;
                        ++itc2->second;
                        ++itc3->second;
                    }
                }
            }
        }
    }
    side1.clean_and_log();
    side2.clean_and_log();
    side3.clean_and_log();
}

void rules::Triangle::link_abda_and_adca(Triangle &abda, Triangle &adca) {
  for (auto ita = abda.side3.stars.begin(); ita != abda.side3.stars.end(); ) {
      auto itb = adca.side1.stars.find(ita->first);
      if (itb == abda.side3.stars.end())
          ita = abda.side3.stars.erase(ita);
      else
          ++ita;
  }
  for (auto itb = adca.side1.stars.begin(); itb != adca.side1.stars.end(); ) {
      auto ita = abda.side3.stars.find(itb->first);
      if (ita == abda.side3.stars.end())
          itb = adca.side1.stars.erase(itb);
      else
          ++itb;
  }
  abda.link_sides();
  adca.link_sides();
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



