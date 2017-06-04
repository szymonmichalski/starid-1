/// *pairs over whole sky*
///
/// star pairs with a separation angle within a given range.
///
#ifndef PAIRS_H
#define PAIRS_H

#include "globals.h"
#include "pointing_vectors.h"
#include "float_int_table.h"

#include <unordered_map>
#include "../libstarid/cereal/access.hpp"
#include "../libstarid/cereal/types/string.hpp"
#include "../libstarid/cereal/types/tuple.hpp"
#include "../libstarid/cereal/types/vector.hpp"
#include "../libstarid/cereal/types/unordered_map.hpp"
#include "../libstarid/Eigen/Core"

namespace starid {

class Pairs {

public:

    /// *pairs map* each star is a map key whose value is a map of star keys it pairs with.
    ///
    std::unordered_map<int, std::unordered_map<int, int>> pairs_map(double angle, double tol_radius);

    /// *init* creates the pairs data structures for all star pairs with a separation less than maximum angle.
    ///
    void init(double max_ang, starid::Sky& sky);

private:

    util::FloatIntTable angletable; // angle, starpairs ndx

    std::vector<std::tuple<double, int, int>> starpairs; // angle, catndx1, catndx2

    std::unordered_map<std::string, int> starpairs_map; // starpairkey, starpairsndx

    std::string pairsKey(int catndx1, int catndx2); // hash key

    friend class cereal::access;
    template <class Archive> void serialize(Archive& ar) {
        ar(starpairs, starpairs_map, angletable);
    }
};

}

#endif
