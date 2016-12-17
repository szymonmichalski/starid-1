#include "pairs_over_whole_sky.h"

void triangles::PairsOverWholeSky::Init(stars::Sensor &sensor)
{
    int starpairsndx = 0;
    int maxcurrstar = sensor.stars.starsvec.size();
    int currstar = 0;
    while (currstar < maxcurrstar) {

        std::vector<int> neighbors = sensor.stars.StarsNearPoint(sensor.stars.starsvec[currstar].uv, sensor.fov);
        for (int i = 0; i < neighbors.size(); ++i) {
            if (currstar == neighbors[i]) continue;

            std::string key = PairsKey(currstar, neighbors[i]);
            auto search = starpairs_map.find(key);
            if (search != starpairs_map.end()) continue; // check map that pair is unique

            double angle = acos( arma::dot( sensor.stars.starsvec[currstar].uv , sensor.stars.starsvec[neighbors[i]].uv ) );
            if (std::fabs(angle) > sensor.fov) continue;

            std::tuple<double, int, int> starpair {angle, currstar, neighbors[i]};
            starpairs.push_back(starpair);
            starpairs_map.insert({key, starpairsndx}); // update map of unique pairs

            std::pair<double,int> angle_pairsndx {angle, starpairsndx};
            angletable.push_back(angle_pairsndx);

            ++starpairsndx;
        }
        ++currstar;
        //std::cout << currstar << std::endl;
    }

    std::sort(angletable.begin(), angletable.end());
}

std::vector<int> triangles::PairsOverWholeSky::StarsFromPairs(double angle, double tolerance)
{
    double minFloat = angle - tolerance;
    double maxFloat = angle + tolerance;
    std::vector<int> intsFromTable;
    auto itlow = std::lower_bound(angletable.begin(), angletable.end(), std::make_pair(minFloat, 0));
    auto ithi = std::upper_bound(angletable.begin(), angletable.end(), std::make_pair(maxFloat, 0));
    for (auto it = itlow; it <= ithi; ++it) {
        auto tablerow = *it;
        intsFromTable.push_back(tablerow.second);
    }
    std::sort(intsFromTable.begin(),intsFromTable.end());

    std::vector<int> starndxs; // ndxs2 lists stars from the pairs
    for (int starpairsndx : intsFromTable) {
        starndxs.push_back(std::get<1>(starpairs[starpairsndx]));
        starndxs.push_back(std::get<2>(starpairs[starpairsndx]));
    }
    std::sort(starndxs.begin(), starndxs.end());
    return starndxs;
}

std::string triangles::PairsOverWholeSky::PairsKey(int catndx1, int catndx2) {
    if (catndx1 > catndx2) {
        int tmp = catndx1;
        catndx1 = catndx2;
        catndx2 = tmp;
    }
    std::string key = std::to_string(catndx1) + std::to_string(catndx2);
    return key;
}

void triangles::PairsOverWholeSky::Status() {
    int sz = angletable.size();
    std::cout << "atable size " << sz
              << " med " << angletable[sz/2].first * 180.0 / arma::datum::pi
              << " max " << angletable[sz-1].first * 180.0 / arma::datum::pi << "\n";
}

