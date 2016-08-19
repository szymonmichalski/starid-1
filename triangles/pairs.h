#ifndef PAIRS_H
#define PAIRS_H

#include "sensor.h"

#include <unordered_map>

namespace triangles {

class Pairs {

public:

    void Init(stars::Sensor &sensor);

    std::vector<int> Candidates(double angle, double tolerance);

    void Status();

private:

    std::vector<std::pair<double, int>>       pair_angle_table; // angle, starpairs ndx
    std::vector<std::tuple<double, int, int>> starpairs; // angle, catndx1, catndx2
    std::unordered_map<std::string, int>      starpairs_map; // starpairkey, starpairsndx

    std::string PairsKey(int& catndx1, int& catndx2); // hash key


};

}

#endif
