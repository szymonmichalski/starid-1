#include "pairs.h"

pairs::Star::Star(int catndxin, stars::Stars& cat, double radius)
{
    catndx = catndxin;
    neighbors = cat.StarsNearPoint(cat.stars[catndx].uv, radius);
}

pairs::Pairs::Pairs() {}
pairs::Pairs::Pairs(stars::Stars& cat, double fov)
{
    int starpairsndx = 0;
    for (uint catndx = 0; catndx < cat.stars.size(); ++catndx) {
        pairs::Star star(catndx, cat, fov);
        for (uint i = 0; i < star.neighbors.size(); ++i) {
            if (star.catndx == star.neighbors[i]) continue;
            int catndx1 = star.catndx;
            int catndx2 = star.neighbors[i];
            std::string key = pairs::Pairs::PairsKey(catndx1, catndx2);
            auto search = starpairs_map.find(key);
            if (search != starpairs_map.end()) continue; // check map that pair is unique

            double angle = acos( arma::dot( cat.stars[catndx1].uv , cat.stars[catndx2].uv ) );
            if (std::fabs(angle) > fov) continue;
            starpairs_map.insert({key, starpairsndx}); // update map of unique pairs

            std::tuple<double, int, int> starpair {angle, catndx1, catndx2};
            starpairs.push_back(starpair);
            std::pair<double,int> apair {angle, starpairsndx};
            atable.push_back(apair);
            ++starpairsndx;
        }
    }
    std::sort(atable.begin(), atable.end());
    afinder.is_neighbors_table(atable);
}

std::vector<int> pairs::Pairs::Candidates(double angle, double tolerance)
{
    std::vector<int> starpairsndxs = afinder.FindNeighbors(angle-tolerance, angle+tolerance);
    std::vector<int> catndxs;
    for (int ndx : starpairsndxs) {
        catndxs.push_back(std::get<1>(starpairs[ndx]));
        catndxs.push_back(std::get<2>(starpairs[ndx]));
    }
    std::sort(catndxs.begin(), catndxs.end());
    return catndxs;
}

void pairs::Pairs::Status() {
    int sz = atable.size();
    std::cout << "atable size " << sz
              << " med " << atable[sz/2].first * 180.0 / arma::datum::pi
              << " max " << atable[sz-1].first * 180.0 / arma::datum::pi << "\n";
}

std::string pairs::Pairs::PairsKey(int& catndx1, int& catndx2) {
    if (catndx1 > catndx2) {
        int tmp = catndx1;
        catndx1 = catndx2;
        catndx2 = tmp;
    }
    std::string key = std::to_string(catndx1) + std::to_string(catndx2);
    return key;
}

