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

    ///
    /// \brief Triangles
    /// \param image
    /// \param pairs
    /// \param tol_radius
    /// \param triMaxCnt
    ///
    Triangles(stars::Image& image, rules::PairsOverWholeSky& pairs,
              double tol_radius, int triMaxCnt);

    ///
    /// \brief identifyCentralStar
    /// \return
    ///
    int identifyCentralStar();

private:

    ///
    /// \brief updateCans
    /// \param ab
    /// \param bc
    /// \return
    ///
    std::unordered_map<int,int> updateCans(std::unordered_multimap<int, int>& ab,
                                          std::unordered_multimap<int, int>& bc);

    rules::PairsOverWholeSky pairsOverWholeSky;
    stars::Image& image;
    double tol_radius;
    int triMaxCnt;
    int starsCnt;
    int triCur;
};

}

#endif
