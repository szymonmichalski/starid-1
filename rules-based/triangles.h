/// **triangles**
///
/// find star triangles in the image, and candidate stars that meet the constraints implicit within the triangle. these constraints are effectively the rules for candidate stars. for example, if a triangle consists of star pairs ab and bc, then the third side is ac.
///
#ifndef TRIPLETS_H
#define TRIPLETS_H
#include "globals.h"
#include "image.h"
#include "pairs_over_whole_sky.h"
#include <eigen/Core>
#include <unordered_map>
#include <map>

namespace rules {

class Triangles
{

public:

    Triangles(stars::Image& image, rules::PairsOverWholeSky& pairs, double tol_radius);

    int identifyCentralStar();

private:

    /// *reduce* remove star pairs that don't agree with constraint sides.
    ///
    void reduce(std::unordered_multimap<int, int>&,
                const std::unordered_multimap<int, int>&,
                const std::unordered_multimap<int, int>&,
                const std::unordered_multimap<int, int>&,
                const std::unordered_multimap<int, int>&);

    void reduce(std::unordered_multimap<int, int>&,
                const std::unordered_multimap<int, int>&);

    /// *stars in three sides* find stars that are present in sidea, sideb, and sidec.
    ///
    std::unordered_map<int,int> starsInThreeSides(const std::unordered_multimap<int, int>& sidea,
                                                  const std::unordered_multimap<int, int>& sideb,
                                                  const std::unordered_multimap<int, int>& sidec);

    /// *stars in two sides* find stars that are present in both sidea and sideb.
    ///
    std::unordered_map<int,int> starsInTwoSides(const std::unordered_multimap<int, int>& sidea,
                                                const std::unordered_multimap<int, int>& sideb);

    /// *merge stars* merge a group of stars into another group of stars
    ///
    void mergeStars(std::unordered_map<int, int>& stars1, const std::unordered_map<int, int>& stars2);

    rules::PairsOverWholeSky pairsOverWholeSky;
    stars::Image& image;
    double tol_radius;
};

}

#endif
