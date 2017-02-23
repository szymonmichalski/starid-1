#include "triangle.h"

rules::Triangle::Triangle(double ang1, double ang2, double ang3,
                          double tol_radius, rules::PairsOverWholeSky& pairs,
                          int teststar)
    : side1(ang1, tol_radius, pairs, teststar),
    side2(ang2, tol_radius, pairs, teststar),
    side3(ang3, tol_radius, pairs, teststar),
    teststar(teststar) {
    prune();
}
rules::Triangle::Triangle(int teststar)
    : side1(teststar),
      side2(teststar),
      side3(teststar),
      teststar(teststar) {

}

void rules::Triangle::update13(TriangleSide &side1new, TriangleSide &side3new) {
    for (auto it1 = side1.stars.begin(); it1 != side1.stars.end(); ) {
        auto it1new = side1new.stars.find(it1->first);
        if (it1new == side1new.stars.end())
            it1 = side1.stars.erase(it1);
        else
            ++it1;
    }
    for (auto it3 = side3.stars.begin(); it3 != side3.stars.end(); ) {
        auto it3new = side3new.stars.find(it3->first);
        if (it3new == side3new.stars.end())
            it3 = side3.stars.erase(it3);
        else
            ++it3;
    }
    prune();
}
void rules::Triangle::update1(TriangleSide &side1new) {
    for (auto it1 = side1.stars.begin(); it1 != side1.stars.end(); ) {
        auto it1new = side1new.stars.find(it1->first);
        if (it1new == side1new.stars.end())
            it1 = side1.stars.erase(it1);
        else
            ++it1;
    }
    prune();
}
void rules::Triangle::update3(TriangleSide &side3new) {
    for (auto it3 = side3.stars.begin(); it3 != side3.stars.end(); ) {
        auto it3new = side3new.stars.find(it3->first);
        if (it3new == side3new.stars.end())
            it3 = side3.stars.erase(it3);
        else
            ++it3;
    }
    prune();
}

void rules::Triangle::side2_side3(double ang2, double ang3,
                            double tol_radius, rules::PairsOverWholeSky &pairs) {
    rules::TriangleSide side2new(ang2, tol_radius, pairs, teststar);
    rules::TriangleSide side3new(ang3, tol_radius, pairs, teststar);
    side2 = side2new;
    side3 = side3new;
    prune();
}

void rules::Triangle::side1_side2(double ang1, double ang2,
                            double tol_radius, rules::PairsOverWholeSky &pairs) {
    rules::TriangleSide side1new(ang1, tol_radius, pairs, teststar);
    rules::TriangleSide side2new(ang2, tol_radius, pairs, teststar);
    side1 = side1new;
    side2 = side2new;
    prune();
}

void rules::Triangle::prune() {
    for (auto itab = side1.stars.begin(); itab != side1.stars.end(); ) {
        auto itca = side3.stars.find(itab->first);
        if (itca == side3.stars.end())
            itab = side1.stars.erase(itab);
        else
            ++itab;
    }
    for (auto itca = side3.stars.begin(); itca != side3.stars.end(); ) {
        auto itab = side1.stars.find(itca->first);
        if (itab == side1.stars.end())
            itca = side3.stars.erase(itca);
        else
            ++itca;
    }

    for (auto it1ab = side1.stars.begin(), end = side1.stars.end(); it1ab != end; ++it1ab) {
        int star1ab = it1ab->first;                     // star 1ab
        auto it1ca = side3.stars.find(star1ab);         // star 1ca
        auto &pairsab = it1ab->second;                  // pairs ab
        auto &pairsca = it1ca->second;                  // pairs ca

        for (auto it2ab = pairsab.begin(), end = pairsab.end(); it2ab != end; ++it2ab) {
            int star2ab = it2ab->first;                 // star 2ab
            auto it2bc = side2.stars.find(star2ab);     // star 2bc
            if (it2bc != side2.stars.end()) {
                auto &pairsbc = it2bc->second;          // pairs bc

                for (auto it3bc = pairsbc.begin(), end = pairsbc.end(); it3bc != end; ++it3bc) {
                    int star3bc = it3bc->first;         // star 3bc
                    auto it3ca = pairsca.find(star3bc); // star 3ca
                    if (it3ca != pairsca.end()) {
                        ++it2ab->second;
                        ++it3bc->second;
                        ++it3ca->second;
                    }
                }
            }
        }
    }
    side1.prune();
    side2.prune();
    side3.prune();
}
