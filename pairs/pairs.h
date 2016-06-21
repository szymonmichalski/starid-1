#ifndef PAIRS_H
#define PAIRS_H

#include "catalog.h"

#include <unordered_map>

namespace pairs {

struct Star {
    Star(int catndxin, base::Catalog& cat, double radius);
    int catndx;
    std::vector<int> neighbors; // catndxs
};

class Pairs {
public:
    Pairs();
    Pairs(base::Catalog& cat, double fov);
    void Status();
    std::vector<int> Candidates(double angle, double tolerance);
private:
    std::vector<std::tuple<double, int, int>> starpairs; // angle, catndx1, catndx2
    std::unordered_map<std::string, int> starpairs_map; // starpairkey, starpairsndx
    std::string PairsKey(int& catndx1, int& catndx2); // hash key
    std::vector<std::pair<double, int>> atable; // angle, starpairs ndx
    base::IndexFinder afinder;
};

}

#endif
