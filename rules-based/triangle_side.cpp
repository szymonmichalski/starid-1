#include "triangle_side.h"

rules::TriangleSide::TriangleSide(double ang, double tol_radius, rules::PairsOverWholeSky& pairs) {
    std::unordered_multimap<int, int> in = pairs.pairsMap2(ang, tol_radius);
    for (auto it = in.begin(), end = in.end(); it != end; ++it) {
        add_pair(it->first, it->second);
    }
}

void rules::TriangleSide::add_pair(int star1, int star2) {
    rules::TriangleSide::inner_map inner;
    inner.insert(std::make_pair(star2,1));
    stars.insert(std::make_pair(star1,inner));
}
