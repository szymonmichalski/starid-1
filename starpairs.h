#ifndef STARPAIRS_H
#define STARPAIRS_H

#include "util.h"
#include "catalog.h"
#include <unordered_map>

namespace starpairs {

struct Star {
    Star(int catndxin, catalog::Catalog& cat, double radius);
    int catndx;
    std::vector<int> neighbors; // catndxs
};

class StarPairs {
public:
    StarPairs(catalog::Catalog& cat, double radius);
private:
    std::vector<std::tuple<double, int, int>> starpairs_; // angle, catndx1, catndx2
    std::unordered_map<std::string, int> starpairs_map_; // starpairkey, starpairsndx
    std::string StarPairKey(int& catndx1, int& catndx2); // hash key
};

}

#endif // STARPAIRS_H
