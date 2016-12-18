#include "pairs_over_whole_sky.h"

void triangles::PairsOverWholeSky::init(stars::Sensor &sensor)
{
    int starpairsndx = 0;
    int maxcurrstar = sensor.stars.starsvec.size();
    int currstar = 0;
    while (currstar < maxcurrstar) {

        std::vector<int> neighbors = sensor.stars.starsNearPoint(sensor.stars.starsvec[currstar].uv, sensor.fov);
        for (int i = 0; i < neighbors.size(); ++i) {
            if (currstar == neighbors[i]) continue;

            std::string key = pairsKey(currstar, neighbors[i]);
            auto search = starpairs_map.find(key);
            if (search != starpairs_map.end()) continue; // check map that pair is unique

            double angle = acos( arma::dot( sensor.stars.starsvec[currstar].uv , sensor.stars.starsvec[neighbors[i]].uv ) );
            if (std::fabs(angle) > sensor.fov) continue;

            std::tuple<double, int, int> starpair {angle, currstar, neighbors[i]};
            starpairs.push_back(starpair);
            starpairs_map.insert({key, starpairsndx}); // update map of unique pairs
            angletable.addPair(angle, starpairsndx);
            ++starpairsndx;
        }
        ++currstar;
        //std::cout << currstar << std::endl;
    }
    angletable.sort();
}

std::vector<int> triangles::PairsOverWholeSky::starsFromPairs(double angle, double tolerance)
{
    std::vector<int> intsFromTable = angletable.findInts(angle-tolerance, angle+tolerance);
    std::vector<int> starndxs; // ndxs2 lists stars from the pairs
    for (int starpairsndx : intsFromTable) {
        starndxs.push_back(std::get<1>(starpairs[starpairsndx]));
        starndxs.push_back(std::get<2>(starpairs[starpairsndx]));
    }
    std::sort(starndxs.begin(), starndxs.end());
    return starndxs;
}

std::string triangles::PairsOverWholeSky::pairsKey(int catndx1, int catndx2) {
    if (catndx1 > catndx2) {
        int tmp = catndx1;
        catndx1 = catndx2;
        catndx2 = tmp;
    }
    std::string key = std::to_string(catndx1) + std::to_string(catndx2);
    return key;
}

void triangles::PairsOverWholeSky::Status() {
}

