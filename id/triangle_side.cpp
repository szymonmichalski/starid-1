#include "triangle_side.h"

rules::TriangleSide::TriangleSide(double ang,
                                  double tolerance,
                                  stars::Pairs& pairs,
                                  int starndx)
    : teststar(starndx)
{
    stars = pairs.pairs_map(ang, tolerance);
}

rules::TriangleSide::TriangleSide(int teststar)
    : teststar(teststar)
{
}

void rules::TriangleSide::append_iterations(TriangleSide &side) {
    stars = side.stars;
    for (auto tmp : side.log_pair_count) log_pair_count.push_back(tmp);
    for (auto tmp : side.log_star_count) log_star_count.push_back(tmp);
    for (auto tmp : side.log_teststar) log_teststar.push_back(tmp);
    has_teststar = side.has_teststar;
}

void::rules::TriangleSide::trim_pairs() {

    for (auto star1 = stars.begin(), end = stars.end(); star1 != end; ++star1) {
        auto &pairs = star1->second;

        for (auto star2 = pairs.begin(); star2 != pairs.end(); ) {

            if (star2->second == 0) {
                star2 = pairs.erase(star2);
            } else {
                star2->second = 0;
                ++star2;
            }
        }
    }

    for (auto star1 = stars.begin(); star1 != stars.end(); ) {
        auto &pairs = star1->second;
        if (pairs.empty())
            star1 = stars.erase(star1);
        else
            ++star1;
    }

    has_teststar = check_teststar(teststar);
    log_star_count.push_back(stars.size());
    log_pair_count.push_back(pair_count());
    log_teststar.push_back(has_teststar);
}

int rules::TriangleSide::pair_count() {
    int result = 0;
    for (auto it1 = stars.begin(), end = stars.end(); it1 != end; ++it1) {
        result += it1->second.size();
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

bool rules::TriangleSide::check_teststar(int starndx) {
    auto it = stars.find(starndx);
    if (it == stars.end()) return false;
    return true;
}
