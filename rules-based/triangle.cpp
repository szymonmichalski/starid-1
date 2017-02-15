#include "triangle.h"

rules::Triangle::Triangle(double angab, double angbc, double angca,
                          double tol_radius, rules::PairsOverWholeSky& pairs) :
    ab(angab, tol_radius, pairs),
    bc(angbc, tol_radius, pairs),
    ca(angca, tol_radius, pairs)
{
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
}
