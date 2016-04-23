#include "angles.h"

pairs::Star::Star(int catndxin, base::Catalog& cat, double radius)
{
    catndx = catndxin;
    neighbors = cat.StarsNearPoint(cat.stars[catndx].uv, radius);
}

pairs::Angles::Angles() {};
pairs::Angles::Angles(base::Catalog& cat, double radius)
{
    int starpairsndx = 0;
    for (uint catndx = 0; catndx < cat.stars.size(); ++catndx) {
        pairs::Star star(catndx, cat, radius);
        for (uint i = 0; i < star.neighbors.size(); ++i) {
            if (star.catndx == star.neighbors[i]) continue;
            int catndx1 = star.catndx;
            int catndx2 = star.neighbors[i];
            std::string key = pairs::Angles::AnglesKey(catndx1, catndx2);
            auto search = starpairs_map.find(key);
            if (search != starpairs_map.end()) continue;
            double angle = acos( arma::dot( cat.stars[catndx1].uv , cat.stars[catndx2].uv ) );
            if (std::fabs(angle) > radius) continue;
            starpairs_map.insert({key, starpairsndx});
            std::tuple<double, int, int> starpair {angle, catndx1, catndx2};
            starpairs.push_back(starpair);
            std::pair<double,int> apair {angle, starpairsndx};
            atable.push_back(apair);
            ++starpairsndx;
        }
    }
    afinder.SetTable(atable);
    std::sort(atable.begin(), atable.end());
}

void pairs::Angles::Status() {
    int sz = atable.size();
    std::cout << "atable size " << sz
              << " med " << atable[sz/2].first * 180.0 / arma::datum::pi
              << " max " << atable[sz-1].first * 180.0 / arma::datum::pi << "\n";
}

std::string pairs::Angles::AnglesKey(int& catndx1, int& catndx2) {
    if (catndx1 > catndx2) {
        int tmp = catndx1;
        catndx1 = catndx2;
        catndx2 = tmp;
    }
    std::string key = std::to_string(catndx1) + std::to_string(catndx2);
    return key;
}

