#include "pairs.h"

void triangles::Pairs::Init(stars::Sensor &sensor)
{
    int starpairsndx = 0;
    for (int starndx = 0; starndx < sensor.stars.starsvec.size(); ++starndx) {

        std::vector<int> neighbors = sensor.stars.StarsNearPoint(sensor.stars.starsvec[starndx].uv, sensor.fov);

        for (int i = 0; i < neighbors.size(); ++i) {
            if (starndx == neighbors[i]) continue;

            std::string key = PairsKey(starndx, neighbors[i]);
            auto search = starpairs_map.find(key);
            if (search != starpairs_map.end()) continue; // check map that pair is unique

            double angle = acos( arma::dot( sensor.stars.starsvec[starndx].uv , sensor.stars.starsvec[neighbors[i]].uv ) );
            if (std::fabs(angle) > sensor.fov) continue;

            std::tuple<double, int, int> starpair {angle, starndx, neighbors[i]};
            std::pair<double,int> pair_angle {angle, starpairsndx};

            starpairs.push_back(starpair);
            starpairs_map.insert({key, starpairsndx}); // update map of unique pairs
            pair_angle_table.push_back(pair_angle);

            ++starpairsndx;
        }
    }

    std::sort(pair_angle_table.begin(), pair_angle_table.end());
}

std::string triangles::Pairs::PairsKey(int& catndx1, int& catndx2) {
    if (catndx1 > catndx2) {
        int tmp = catndx1;
        catndx1 = catndx2;
        catndx2 = tmp;
    }
    std::string key = std::to_string(catndx1) + std::to_string(catndx2);
    return key;
}

std::vector<int> triangles::Pairs::Candidates(double angle, double tolerance)
{
    std::vector<int> starpairsndxs; // = afinder.FindNeighbors(angle-tolerance, angle+tolerance);
    // search pair_angle_table for ndxs into starpairs

    std::vector<int> candndxs;
    for (int ndx : starpairsndxs) {
        candndxs.push_back(std::get<1>(starpairs[ndx]));
        candndxs.push_back(std::get<2>(starpairs[ndx]));
    }
    std::sort(candndxs.begin(), candndxs.end());
    return candndxs;
}

void triangles::Pairs::Status() {
    int sz = pair_angle_table.size();
    std::cout << "atable size " << sz
              << " med " << pair_angle_table[sz/2].first * 180.0 / arma::datum::pi
              << " max " << pair_angle_table[sz-1].first * 180.0 / arma::datum::pi << "\n";
}



