#include "pairs_over_whole_sky.h"

void rules::PairsOverWholeSky::init(double max_ang, stars::Sky& sky)
{
    int pairndx = 0;

    for(auto star : sky.stars) {
      std::vector<int> starndxs = sky.starsNearPoint(star.x, star.y, star.z);
      starndxs.push_back(star.starndx);

      for (auto starndx1 : starndxs) {

        for (auto starndx2 : starndxs) {
          if (starndx1 == starndx2) continue;

          std::string key = pairsKey(sky.stars[starndx1].starndx, sky.stars[starndx2].starndx);
          auto search = starpairs_map.find(key);
          if (search != starpairs_map.end()) continue; // check map that pair is unique

          double angle = std::acos( (sky.stars[starndx1].x * sky.stars[starndx2].x) + (sky.stars[starndx1].y * sky.stars[starndx2].y) + (sky.stars[starndx1].z * sky.stars[starndx2].z));
          if (std::abs(angle) > max_ang) continue; // max pair angle

          std::tuple<double, int, int> starpair {angle, starndx1, starndx2};
          starpairs.push_back(starpair);
          starpairs_map.insert({key, pairndx}); // update map of unique pairs
          angletable.addPair(angle, pairndx);
          ++pairndx;
        }
      }
    }
    angletable.sort();
}

std::unordered_map<int, std::unordered_map<int, int>> rules::PairsOverWholeSky::pairs_map(double angle, double tol_radius) {
    std::unordered_map<int, std::unordered_map<int, int>> stars;

    double ang1 = angle - tol_radius;
    double ang2 = angle + tol_radius;
    double epsilon = 1.0;

    if (ang1 <= 0) ang1 = 0;
    if (ang2 <= epsilon * tol_radius) ang2 = epsilon * tol_radius;

    if (ang1 >= stars::star_pair_angle_limit - epsilon * tol_radius) ang1 = stars::star_pair_angle_limit - epsilon * tol_radius;
    if (ang2 >= stars::star_pair_angle_limit) ang2 = stars::star_pair_angle_limit;

    std::vector<int> intsFromTable = angletable.findInts(ang1, ang2);
    for (auto ndx : intsFromTable) {
        int star1 = std::get<1>(starpairs[ndx]);
        int star2 = std::get<2>(starpairs[ndx]);

        auto it1 = stars.find(star1);
        if (it1 != stars.end()) {
            auto &pairs1 = it1->second;
            pairs1.emplace(std::make_pair(star2,0)); // initial value for pair star key is 0
        } else {
            std::unordered_map<int, int> pairs1;
            pairs1.emplace(std::make_pair(star2,1));
            stars.emplace(std::make_pair(star1,pairs1));
        }

        auto it2 = stars.find(star2);
        if (it2 != stars.end()) {
            auto &pairs2 = it2->second;
            pairs2.emplace(std::make_pair(star1,0)); // initial value for pair star key is 0
        } else {
            std::unordered_map<int, int> pairs2;
            pairs2.emplace(std::make_pair(star1,1));
            stars.emplace(std::make_pair(star2,pairs2));
        }
    }

    return stars;
};

std::string rules::PairsOverWholeSky::pairsKey(int catndx1, int catndx2) {
    if (catndx1 > catndx2) {
        int tmp = catndx1;
        catndx1 = catndx2;
        catndx2 = tmp;
    }
    std::string key = std::to_string(catndx1) + std::to_string(catndx2);
    return key;
}
