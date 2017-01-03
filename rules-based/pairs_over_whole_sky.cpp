#include "pairs_over_whole_sky.h"

void rules::PairsOverWholeSky::init(stars::Sensor& sensor)
{
    int pairndx = 0;
    for(auto star : sensor.sky.stars) {
        std::vector<int> neighborndxs = sensor.sky.starsNearPoint(star.uv, sensor.fov);
        for (auto neighborndx : neighborndxs) {
            if (star.starndx == neighborndx) continue;
            std::string key = pairsKey(star.starndx, sensor.sky.stars[neighborndx].starndx);
            auto search = starpairs_map.find(key);
            if (search != starpairs_map.end()) continue; // check map that pair is unique
            double angle = acos( arma::dot( star.uv , sensor.sky.stars[neighborndx].uv ) );
            if (std::fabs(angle) > sensor.fov) continue;
            std::tuple<double, int, int> starpair {angle, star.starndx, neighborndx};
            starpairs.push_back(starpair);
            starpairs_map.insert({key, pairndx}); // update map of unique pairs
            angletable.addPair(angle, pairndx);
            ++pairndx;
        }
    }
    angletable.sort();
}

std::vector<int> rules::PairsOverWholeSky::starsFromPairs(double angle, double tolerance)
{
    std::vector<int> intsFromTable = angletable.findInts(angle-tolerance, angle+tolerance);
    std::vector<int> starndxs; // list of stars from the pairs
    for (auto pairndx : intsFromTable) {
        starndxs.push_back(std::get<1>(starpairs[pairndx]));
        starndxs.push_back(std::get<2>(starpairs[pairndx]));
    }
    std::sort(starndxs.begin(), starndxs.end());
    return starndxs;
}

std::string rules::PairsOverWholeSky::pairsKey(int catndx1, int catndx2) {
    if (catndx1 > catndx2) {
        int tmp = catndx1;
        catndx1 = catndx2;
        catndx2 = tmp;
    }
    std::string key = std::to_string(catndx1) + std::to_string(catndx2);
    return key;
}

void rules::PairsOverWholeSky::Status() {
}

