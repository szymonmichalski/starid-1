#include "triangle_side.h"

rules::TriangleSide::TriangleSide(double ang, double tol_radius, rules::PairsOverWholeSky& pairs,
                                  int starndx)
    : teststar(starndx) {
    stars = pairs.pairs_map(ang, tol_radius);
    log_star_count.push_back(stars.size());
    log_pair_count.push_back(pair_count());
    log_teststar.push_back(has_star(starndx));
}
rules::TriangleSide::TriangleSide(int teststar)
    : teststar(teststar) {

}

void rules::TriangleSide::intersect_stars(TriangleSide &other_side) {
    for (auto it1 = stars.begin(); it1 != stars.end(); ) {
        auto it2 = other_side.stars.find(it1->first);
        if (it2 == other_side.stars.end())
            it1 = stars.erase(it1);
        else
            ++it1;
    }
}


void::rules::TriangleSide::prune() {
    for (auto it1 = stars.begin(); it1 != stars.end(); ) {
        auto &pairs = it1->second;
        for (auto it2 = pairs.begin(); it2 != pairs.end(); ) {
            if (it2->second == 0) {
                it2 = pairs.erase(it2);
            } else {
                it2->second = 0;
                ++it2;
            }
        }
        if (pairs.empty())
            it1 = stars.erase(it1);
        else
            ++it1;
    }
    log_star_count.push_back(stars.size());
    log_pair_count.push_back(pair_count());
    log_teststar.push_back(has_star(teststar));
}

int rules::TriangleSide::pair_count() {
    int result = 0;
    for (auto it1 = stars.begin(), end = stars.end(); it1 != end; ++it1) {
        result += it1->second.size();
    }
    return result;
}

void rules::TriangleSide::close_loop(TriangleSide &sideb, TriangleSide &sidec) {

    for (auto it1a = stars.begin(); it1a != stars.end(); ) {
        bool is_loop_closed = false;

        int star1a = it1a->first;                    // star 1a
        auto it1c = sidec.stars.find(star1a);        // star 1c
        if (it1c == sidec.stars.end()) {
            it1a = stars.erase(it1a);
            continue;
        }
        auto &pairsa = it1a->second;                 // pairs a
        auto &pairsc = it1c->second;                 // pairs c

        for (auto it2a = pairsa.begin(); it2a != pairsa.end(); ) {
            int star2a = it2a->first;                // star 2a
            auto it2b = sideb.stars.find(star2a);    // star 2b
            if (it2b != sideb.stars.end()) {
                auto &pairsb = it2b->second;         // pairs b

                for (auto it3b = pairsb.begin(); it3b != pairsb.end(); ) {
                    int star3b = it3b->first;        // star 3b
                    auto it3c = pairsc.find(star3b); // star 3c
                    if (it3c != pairsc.end()) is_loop_closed = true;
                    ++it3b;
                }
            }

            if (is_loop_closed)
                ++it2a;
            else
                it2a = pairsa.erase(it2a);
        }

        if (pairsa.empty())
            it1a = stars.erase(it1a);
        else
            ++it1a;
    }
    log_star_count.push_back(stars.size());
}

void rules::TriangleSide::constraint_side(TriangleSide &ll, TriangleSide &lu,
                                          TriangleSide &rl, TriangleSide &ru) {
    for (auto it1 = stars.begin(); it1 != stars.end(); ) {
        int star1 = it1->first;
        auto &inner = it1->second;
        for (auto it2 = inner.begin(); it2 != inner.end(); ) {
            int star2 = it2->first;
            if ( (ll.has_star(star1) && lu.has_star(star1)) &&
                 (rl.has_star(star2) && ru.has_star(star2)) ) ++it2;
            else if ( (ll.has_star(star2) && lu.has_star(star2)) &&
                      (rl.has_star(star1) && ru.has_star(star1)) ) ++it2;
            //            if ( (ll.has_star(star1) || lu.has_star(star1)) &&
            //                 (rl.has_star(star2) || ru.has_star(star2)) ) ++it2;
            //            else if ( (ll.has_star(star2) || lu.has_star(star2)) &&
            //                      (rl.has_star(star1) || ru.has_star(star1)) ) ++it2;
            else it2 = inner.erase(it2);
        }
        if (inner.empty()) it1 = stars.erase(it1); else ++it1;
    }
    log_star_count.push_back(stars.size());
}

std::unordered_map<int, int> rules::TriangleSide::stars_in_three_sides(TriangleSide &sideb, TriangleSide &sidec) {
    std::unordered_map<int, int> result;
    for (auto it1 = stars.begin(), end = stars.end(); it1 != end; ++it1) {
        int star = it1->first;
        if (sideb.has_star(star) && sidec.has_star(star)) result.emplace(star, 1);
    }
    return result;
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
