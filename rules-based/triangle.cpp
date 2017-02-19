#include "triangle.h"

rules::Triangle::Triangle(double angab, double angbc, double angca,
                          double tol_radius, rules::PairsOverWholeSky& pairs) :
    side1(angab, tol_radius, pairs),
    side2(angbc, tol_radius, pairs),
    side3(angca, tol_radius, pairs) {
    prune();
}

void rules::Triangle::update_side1_side3(TriangleSide &abnew, TriangleSide &canew) {
    side1.stars = abnew.stars;
    side3.stars = canew.stars;
    prune();
}


void rules::Triangle::side2_side3(double angbd, double angda,
                            double tol_radius, rules::PairsOverWholeSky& pairs) {
    rules::TriangleSide bd(angbd, tol_radius, pairs);
    rules::TriangleSide da(angda, tol_radius, pairs);
    side2 = bd;
    side3 = da;
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
        auto it1ca = side3.stars.find(star1ab);            // star 1ca
        auto &pairsab = it1ab->second;                  // pairs ab
        auto &pairsca = it1ca->second;                  // pairs ca

        for (auto it2ab = pairsab.begin(), end = pairsab.end(); it2ab != end; ++it2ab) {
            int star2ab = it2ab->first;                 // star 2ab
            auto it2bc = side2.stars.find(star2ab);        // star 2bc
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
