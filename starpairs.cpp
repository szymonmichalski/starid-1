#include "starpairs.h"

starpairs::Star::Star(int catndxin, catalog::Catalog& cat, double radius) {
    catndx = catndxin;
    neighbors = cat.StarsNearPoint(cat.stars_[catndx].uvec, radius);
}

starpairs::StarPairs::StarPairs(catalog::Catalog& cat, double radius) {
    int starpairsndx = 0;
    for (int catndx = 0; catndx < cat.stars_.size(); ++catndx) {
        starpairs::Star star(catndx, cat, radius);
        for (int i = 0; i < star.neighbors.size(); ++i) {
            if (star.catndx == star.neighbors[i]) continue;
            int catndx1 = star.catndx;
            int catndx2 = star.neighbors[i];
            std::string key = starpairs::StarPairs::StarPairKey(catndx1, catndx2);
            auto search = starpairs_map_.find(key);
            if (search != starpairs_map_.end()) continue;
            starpairs_map_.insert({key, starpairsndx});
            double angle = 0.0;
            std::tuple<double, int, int> starpair {angle, catndx1, catndx2};
            starpairs_.push_back(starpair);
            ++starpairsndx;
        }
    }
}

std::string starpairs::StarPairs::StarPairKey(int& catndx1, int& catndx2) {
    if (catndx1 > catndx2) {
        int tmp = catndx1;
        catndx1 = catndx2;
        catndx2 = tmp;
    }
    std::string key = std::to_string(catndx1) + std::to_string(catndx2);
    return key;
}

