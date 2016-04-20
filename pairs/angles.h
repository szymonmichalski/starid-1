#ifndef ANGLES_H
#define ANGLES_H

#include "geometry.h"
#include "catalog.h"
#include "indexfinder.h"

#include <unordered_map>

namespace pairs {

struct Star {
    Star(int catndxin, base::Catalog& cat, double radius);
    int catndx;
    std::vector<int> neighbors; // catndxs
};

class Angles {
public:
    Angles();
    Angles(base::Catalog& cat, double radius);
private:
    std::vector<std::tuple<double, int, int>> starpairs; // angle, catndx1, catndx2
    std::unordered_map<std::string, int> starpairs_map; // starpairkey, starpairsndx
    std::string AnglesKey(int& catndx1, int& catndx2); // hash key
    std::vector<std::pair<double, int>> atable; // angle, starpairs ndx
    base::IndexFinder afinder;
};

}

#endif // STARPAIRS_H
