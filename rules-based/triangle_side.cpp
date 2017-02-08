#include "triangle_side.h"

rules::TriangleSide::TriangleSide(double ang, double tol_radius, rules::PairsOverWholeSky& pairs) {
    stars = pairs.pairsMap3(ang, tol_radius);
    sizeLog.push_back(stars.size());
}

std::map<int, int> rules::TriangleSide::summary() {
    std::map<int, int> result;
    for (auto it = stars.begin(), end = stars.end(); it != end; ++it) {
        auto &inner = it->second;
        result.emplace(it->first, inner.size());
    }
    return result;
}

std::vector<int> rules::TriangleSide::getSizeLog() {
    return sizeLog;
}

bool rules::TriangleSide::hasStar(int starndx) {
    auto it = stars.find(starndx);
    if (it == stars.end()) return false;
    return true;
}

void rules::TriangleSide::constraintSide(const TriangleSide &ll, const TriangleSide &lu,
                                         const TriangleSide &rl, const TriangleSide &ru) {
    // picture the bc case, ll left lower ab, lu left upper db
    // rl right lower ac, ru right upper dc
    for (auto it1 = stars.begin(); it1 != stars.end(); ) {
        int star1 = it1->first;
        auto &inner = it1->second;
        for (auto it2 = inner.begin(); it2 != inner.end(); ) {
            int star2 = it2->first;

        }
    }
    sizeLog.push_back(stars.size());
}
