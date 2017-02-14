/// **triangles**
///
/// find star triangles in the image, and candidate stars that meet the constraints implicit within the triangle. these constraints are effectively the rules for candidate stars. for example, if a triangle consists of star pairs ab and bc, then the third side is ac.
///
#ifndef TRIPLETS_H
#define TRIPLETS_H
#include "triangle.h"
#include "triangle_side.h"
#include "pairs_over_whole_sky.h"
#include "globals.h"
#include "image.h"
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

    /// *update stars* include the latest results
    ///
    void update_stars(std::unordered_map<int, int>& stars1, const std::unordered_map<int, int>& stars2);

    rules::PairsOverWholeSky pairsOverWholeSky;
    stars::Image& image;
    double tol_radius;
};

}

#endif
