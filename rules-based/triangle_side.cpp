#include "triangle_side.h"

rules::TriangleSide::TriangleSide(double ang, double tol_radius, rules::PairsOverWholeSky& pairs) {
    stars = pairs.pairs_map(ang, tol_radius);
    log_size.push_back(stars.size());
}

std::map<int, int> rules::TriangleSide::summary() {
    std::map<int, int> result;
    for (auto it = stars.begin(), end = stars.end(); it != end; ++it) {
        auto &inner = it->second;
        result.emplace(it->first, inner.size());
    }
    return result;
}

bool rules::TriangleSide::has_star(int starndx) {
    auto it = stars.find(starndx);
    if (it == stars.end()) return false;
    return true;
}

void rules::TriangleSide::constraint_side(TriangleSide &ll, TriangleSide &lu,
                                          TriangleSide &rl, TriangleSide &ru) {
    for (auto it1 = stars.begin(); it1 != stars.end(); ) {
        int star1 = it1->first;
        auto &inner = it1->second;
        for (auto it2 = inner.begin(); it2 != inner.end(); ) {
            int star2 = it2->first;
            if ( (ll.has_star(star1) || lu.has_star(star1)) &&
                 (rl.has_star(star2) || ru.has_star(star2)) ) ++it2;
            else if ( (ll.has_star(star2) || lu.has_star(star2)) &&
                      (rl.has_star(star1) || ru.has_star(star1)) ) ++it2;
            else it2 = inner.erase(it2);
        }
        if (inner.empty()) it1 = stars.erase(it1); else ++it1;
    }
    log_size.push_back(stars.size());
}

void rules::TriangleSide::reduce(TriangleSide &side, TriangleSide &constraint_side) {
    for (auto it1 = stars.begin(); it1 != stars.end(); ) {
        int star1 = it1->first;
        if (!side.has_star(star1)) {
            it1 = stars.erase(it1);
            continue;
        }
        auto &inner = it1->second;
        for (auto it2 = inner.begin(); it2 != inner.end(); ) {
            int star2 = it2->first;
            if (constraint_side.has_star(star2)) {
                ++it2;
            } else {
                it2 = inner.erase(it2);
            }
        }
        if (inner.empty()) it1 = stars.erase(it1); else ++it1;
    }
    log_size.push_back(stars.size());
}

std::unordered_map<int, int> rules::TriangleSide::stars_in_three_sides(TriangleSide &side1, TriangleSide &side2) {
    std::unordered_map<int, int> stars;

    return stars;
}
