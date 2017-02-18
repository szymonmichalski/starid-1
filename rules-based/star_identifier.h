/// **star identifier**
///
/// find star triangles in the image, and candidate stars that meet the constraints implicit within the triangle. these constraints are effectively the rules for candidate stars. for example, if a triangle consists of star pairs ab and bc, then the third side is ac.
///
#ifndef STARIDENTIFIER_H
#define STARIDENTIFIER_H
#include "triangle.h"
#include "triangle_side.h"
#include "pairs_over_whole_sky.h"
#include "globals.h"
#include "image.h"
#include <eigen/Core>
#include <unordered_map>
#include <map>

namespace rules {

class StarIdentifier
{

public:

    StarIdentifier(stars::Image& image, rules::PairsOverWholeSky& pairs, double tol_radius);

    int identifyCentralStar();

private:

    /// *update stars* include the latest results
    ///
    void update_stars(std::unordered_map<int, int>& stars1, const std::unordered_map<int, int>& stars2);

    rules::PairsOverWholeSky all_pairs;
    stars::Image& image;
    double tol_radius;
};

}

#endif
