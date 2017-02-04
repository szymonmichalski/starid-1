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

namespace rules {

class Triangles
{

public:

    Triangles(stars::Image& image, rules::PairsOverWholeSky& pairs,
              double tol_radius, int triMaxCnt);

    int identifyCentralStar();

private:

    /// *constrain side* the length of a triangle side is constrained by the lengths of the other two sides. star pairs in the side must have one member in constraint side a, and the other member in constraint side b. our constraint here is stronger. star pairs in the side must have one member that is both constraint sides.
    ///
    void constrainSide(std::unordered_multimap<int, int>& side,
                       const std::unordered_multimap<int, int>& constra,
                       const std::unordered_multimap<int, int>& constrb);

    /// *reduce side* remove all pairs that don't have a member in the other side. this immediately reduces that possible contents of the side.
    void reduceSide(std::unordered_multimap<int, int>& side,
                    const std::unordered_multimap<int, int>& constr);


    /// *find stars in both sides* find stars that are present in both sidea and sideb.
    ///
    std::unordered_map<int,int> findStarsInBothSides(const std::unordered_multimap<int, int>& sidea,
                                                     const std::unordered_multimap<int, int>& sideb);

    rules::PairsOverWholeSky pairsOverWholeSky;
    stars::Image& image;
    double tol_radius;
    int triMaxCnt;
    int starsCnt;
    int triCur;
};

}

#endif
