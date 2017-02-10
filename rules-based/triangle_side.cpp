#include "triangle_side.h"

rules::TriangleSide::TriangleSide(double ang, double tol_radius, rules::PairsOverWholeSky& pairs) {
    stars = pairs.pairsMap3(ang, tol_radius);
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
        bool found = false;
        for (auto it2 = inner.begin(), end = inner.end(); it2 != end; ++it2) {
            int star2 = it2->first;
            if ( (ll.has_star(star1) && lu.has_star(star1) &&
                  rl.has_star(star2) && ru.has_star(star2)) ||
                 (ll.has_star(star2) && lu.has_star(star2) &&
                  rl.has_star(star1) && ru.has_star(star1)) ) {found = true; break;}
        }
        if (found) ++it1; else it1 = stars.erase(it1);
    }
    log_size.push_back(stars.size());
}

void rules::TriangleSide::reduce(TriangleSide &side, TriangleSide &constraint_side) {

}

std::unordered_map<int, int> rules::TriangleSide::stars_in_three_sides(TriangleSide &side1, TriangleSide &side2) {
    std::unordered_map<int, int> stars;

    return stars;
}
