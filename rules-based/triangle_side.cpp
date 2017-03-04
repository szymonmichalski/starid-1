#include "triangle_side.h"

rules::TriangleSide::TriangleSide(double ang, double tol_radius, rules::PairsOverWholeSky& pairs,
                                  int starndx)
  : teststar(starndx) {
  stars = pairs.pairs_map(ang, tol_radius);
//  log_star_count.push_back(stars.size());
//  log_pair_count.push_back(pair_count());
//  log_teststar.push_back(has_teststar(starndx));
}

rules::TriangleSide::TriangleSide(int teststar)
  : teststar(teststar) {

}

void rules::TriangleSide::refresh_pairs(TriangleSide &side)
{
  for (auto it1 = stars.begin(), end = stars.end(); it1 != end; ++it1) {
    auto it2 = side.stars.find(it1->first);
    it1->second = it2->second;
  }
}

void rules::TriangleSide::intersect_stars(TriangleSide &sidea, TriangleSide &sideb) {
  for (auto ita = sidea.stars.begin(); ita != sidea.stars.end(); ) {
    auto itb = sideb.stars.find(ita->first);
    if (itb == sideb.stars.end())
      ita = sidea.stars.erase(ita);
    else
      ++ita;
  }
  for (auto itb = sideb.stars.begin(); itb != sideb.stars.end(); ) {
    auto ita = sidea.stars.find(itb->first);
    if (ita == sidea.stars.end())
      itb = sideb.stars.erase(itb);
    else
      ++itb;
  }
}

void::rules::TriangleSide::prune_pairs() {
  for (auto it1 = stars.begin(); it1 != stars.end(); ) {
    auto &pairs = it1->second;
    for (auto it2 = pairs.begin(); it2 != pairs.end(); ) {
      auto it3 = stars.find(it2->first);
      if (it2->second == 0 || it3 == stars.end()) {
      //if (it2->second == 0) {
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
  log_teststar.push_back(has_teststar(teststar));
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

bool rules::TriangleSide::has_teststar(int starndx) {
  auto it = stars.find(starndx);
  if (it == stars.end()) return false;
  return true;
}
