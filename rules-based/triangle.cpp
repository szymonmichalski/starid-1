#include "triangle.h"

rules::Triangle::Triangle(double angab, double angbc, double angca,
                          double tol_radius, rules::PairsOverWholeSky& pairs) :
    ab(angab, tol_radius, pairs),
    bc(angbc, tol_radius, pairs),
    ca(angca, tol_radius, pairs) {
    prune();
}

void rules::Triangle::bd_da(double angbd, double angda,
                            double tol_radius, rules::PairsOverWholeSky& pairs) {
    rules::TriangleSide bd(angbd, tol_radius, pairs);
    rules::TriangleSide da(angda, tol_radius, pairs);
    bc = bd;
    ca = da;
    prune();
}


void rules::Triangle::prune() {
    for (auto itab = ab.stars.begin(); itab != ab.stars.end(); ) {
        auto itca = ca.stars.find(itab->first);
        if (itca == ca.stars.end())
            itab = ab.stars.erase(itab);
        else
            ++itab;
    }
    for (auto itca = ca.stars.begin(); itca != ca.stars.end(); ) {
        auto itab = ab.stars.find(itca->first);
        if (itab == ab.stars.end())
            itca = ca.stars.erase(itca);
        else
            ++itca;
    }

    for (auto it1ab = ab.stars.begin(), end = ab.stars.end(); it1ab != end; ++it1ab) {
        int star1ab = it1ab->first;                     // star 1ab
        auto it1ca = ca.stars.find(star1ab);            // star 1ca
        auto &pairsab = it1ab->second;                  // pairs ab
        auto &pairsca = it1ca->second;                  // pairs ca

        for (auto it2ab = pairsab.begin(), end = pairsab.end(); it2ab != end; ++it2ab) {
            int star2ab = it2ab->first;                 // star 2ab
            auto it2bc = bc.stars.find(star2ab);        // star 2bc
            if (it2bc != bc.stars.end()) {
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
    ab.prune();
    bc.prune();
    ca.prune();
}

void rules::Triangle::fourth_star(double angda, double angdb, double angdc) {
    // abd case
    // acd case
    prune();
}
