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
    side1.intersect_stars(side3);
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

void rules::Triangle::side2_side3(double ang2, double ang3,
                            double tol_radius, rules::PairsOverWholeSky &pairs) {
    rules::TriangleSide side2new(ang2, tol_radius, pairs, teststar);
    rules::TriangleSide side3new(ang3, tol_radius, pairs, teststar);
    side2 = side2new;
    side3 = side3new;
    link_sides();
}

void rules::Triangle::side1_side2(double ang1, double ang2,
                            double tol_radius, rules::PairsOverWholeSky &pairs) {
    rules::TriangleSide side1new(ang1, tol_radius, pairs, teststar);
    rules::TriangleSide side2new(ang2, tol_radius, pairs, teststar);
    side1 = side1new;
    side2 = side2new;
    link_sides();
}



