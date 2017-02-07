#include "triangle_side.h"

rules::TriangleSide::TriangleSide(double ang, double tol_radius, rules::PairsOverWholeSky& pairs) {
    stars = pairs.pairsMap3(ang, tol_radius);
}

std::map<int, int> rules::TriangleSide::status() {
    std::map<int, int> result;
    for (auto it = stars.begin(), end = stars.end(); it != end; ++it) {
        auto &inner = it->second;
        result.emplace(it->first, inner.size());
    }
    return result;
}

