#ifndef STARPAIRS_H
#define STARPAIRS_H

#include "geometry.h"
#include "catalog.h"
#include "indexfinder.h"
#include <unordered_map>
#include <armadillo>
using namespace arma;

namespace starpairs {

struct Star {
    Star(int catndxin, catalog::Catalog& cat, double radius);
    int catndx;
    std::vector<int> neighbors; // catndxs
};

class StarPairs {
public:
    StarPairs();
    StarPairs(catalog::Catalog& cat, double radius);
private:
    std::vector<std::tuple<double, int, int>> starpairs; // angle, catndx1, catndx2
    std::unordered_map<std::string, int> starpairs_map; // starpairkey, starpairsndx
    std::string StarPairKey(int& catndx1, int& catndx2); // hash key
    std::vector<std::pair<double, int>> atable; // angle, starpairs ndx
    indexfinder::IndexFinder afinder;
};

}

#endif // STARPAIRS_H
