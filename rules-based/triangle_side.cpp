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

void rules::TriangleSide::append_iterations(TriangleSide &side) {
  stars = side.stars;
  for (auto tmp : side.log_pair_count) log_pair_count.push_back(tmp);
  for (auto tmp : side.log_star_count) log_star_count.push_back(tmp);
  for (auto tmp : side.log_teststar) log_teststar.push_back(tmp);
  has_teststar = side.has_teststar;
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
