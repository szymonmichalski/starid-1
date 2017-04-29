/// *triangle side*
///
/// for adding, finding, removing, etc star pairs to a triangle side. one objective here is to work with maps of unique star keys, one key per star, rather than maps with multiple keys per star. this means using unordered_map, not unordered_multimap.
///
#ifndef TRIANGLE_SIDE_H
#define TRIANGLE_SIDE_H

#include "sky.h"
#include "pairs.h"
#include <unordered_map>
#include <map>

namespace starid {

class TriangleSide {

public:

    /// *stars* each star is a map key whose value is a map of star keys it pairs with
    ///
    std::unordered_map<int, std::unordered_map<int, int>> stars;

    /// *trim pairs* remove pairs that have value zero or are no longer stars. then remove stars that have no pairs.
    ///
    void trim_pairs();

    /// *append iterations* append the iterations contained in another side
    ///
    void append_iterations(TriangleSide &side);

    std::vector<int> log_star_count;
    std::vector<int> log_pair_count;
    std::vector<bool> log_teststar;
    int teststar;
    bool has_teststar;

    TriangleSide(double ang,
                 double tolerance,
                 starid::Pairs& pairs,
                 int teststar);

    TriangleSide(int teststar);

    std::map<int, int> summary();
    bool check_teststar(int teststar);
    int pair_count();

private:

};

}

#endif // TRIANGLE_SIDE_H
