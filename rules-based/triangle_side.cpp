#include "triangle_side.h"

void rules::TriangleSide::close_loop(TriangleSide &sideb, TriangleSide &sidec) {
    for (auto it1a = stars.begin(); it1a != stars.end(); ) {

        int star1a = it1a->first;                 // star1 in sidea is star1a
        auto it1c = sidec.stars.find(star1a);     // star1 in sidec is star1c
        if (it1c == sidec.stars.end()) {
            it1a = stars.erase(it1a);
            continue;
        }
        auto &innerc = it1c->second;

        bool is_loop_closed = false;
        auto &innera = it1a->second;
        for (auto it2a = innera.begin(); it2a != innera.end(); ) {
            int star2a = it2a->first;             // star2 in sidea is star2a
            auto it2b = sideb.stars.find(star2a); // star2 in sideb is star2b
            if (it2b != sideb.stars.end()) {
                auto &innerb = it2b->second;
                for (auto it3b = innerb.begin(); it3b != innerb.end(); ) {
                    int star3b = it3b->first;         // star3 in sideb is star3b
                    auto it3c = innerc.find(star3b);  // star3 in sidec is star3c
                    if (it3c != innerc.end()) is_loop_closed = true;
                    ++it3b;
                }
            }
            if (is_loop_closed)
                ++it2a;
            else
                it2a = innera.erase(it2a);
        }

        if (innera.empty())
            it1a = stars.erase(it1a);
        else
            ++it1a;
    }
    log_size.push_back(stars.size());
}

void rules::TriangleSide::constraint_side(TriangleSide &ll, TriangleSide &lu,
                                          TriangleSide &rl, TriangleSide &ru) {
    for (auto it1 = stars.begin(); it1 != stars.end(); ) {
        int star1 = it1->first;
        auto &inner = it1->second;
        for (auto it2 = inner.begin(); it2 != inner.end(); ) {
            int star2 = it2->first;
//            if ( (ll.has_star(star1) && lu.has_star(star1)) &&
//                 (rl.has_star(star2) && ru.has_star(star2)) ) ++it2;
//            else if ( (ll.has_star(star2) && lu.has_star(star2)) &&
//                      (rl.has_star(star1) && ru.has_star(star1)) ) ++it2;
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

std::unordered_map<int, int> rules::TriangleSide::stars_in_three_sides(TriangleSide &side1, TriangleSide &side2) {
    std::unordered_map<int, int> stars;

    return stars;
}

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
