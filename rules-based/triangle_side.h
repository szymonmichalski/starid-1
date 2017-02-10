/// **triangle side**
///
/// for adding, finding, removing, etc star pairs to a triangle side. one objective here is to work with maps of unique star keys, one key per star, rather than maps with multiple keys per star. this means using unordered_map, not unordered_multimap.
///
#ifndef TRIANGLE_SIDE_H
#define TRIANGLE_SIDE_H
#include <unordered_map>
#include <map>
#include "pairs_over_whole_sky.h"

namespace rules {

class TriangleSide {

public:

    std::vector<int> log_size;

    TriangleSide(double ang, double tol_radius, rules::PairsOverWholeSky& pairs);

    /// *summary* returns a sorted map of stars with the initial number of pairs. the pairs become outdatated over time as stars are removed from the side.
    ///
    std::map<int, int> summary();

    /// *has star* return true if star is in the side
    ///
    bool has_star(int starndx);

    /// *constraint side* this side is shared by two adjacent triangles. star pair members have to also be in appropriate combinations of the other four triangle sides. picture the bc case, ll left lower ab, lu left upper db, rl right lower ac, ru right upper dc
    ///
    void constraint_side(TriangleSide &ll, TriangleSide &lu,
                        TriangleSide &rl, TriangleSide &ru);

    /// *reduce*
    ///
    void reduce(TriangleSide &side, TriangleSide &constraint_side);

    /// *stars in three sides* merge stars from ad, ab, ac
    ///
    std::unordered_map<int, int> stars_in_three_sides(TriangleSide &side1, TriangleSide &side2);

private:

    /// *stars* each star is a map key whose value is a map of star keys it pairs with
    ///
    std::unordered_map<int, std::unordered_map<int, int>> stars;


};

}

#endif // TRIANGLE_SIDE_H
