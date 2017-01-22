#ifndef TRIPLETS_H
#define TRIPLETS_H

#include "image.h"
#include "pairs_over_whole_sky.h"
#include <eigen/Core>

namespace rules {

class Triangles
{

public:

    Triangles(stars::Image& image,
              rules::PairsOverWholeSky& pairs,
              double triTol,
              int triMaxCnt);

    int identifyCentralStar();

private:

    Eigen::Matrix<int, Eigen::Dynamic, 2> findRelatedPairs(Eigen::Matrix<int, Eigen::Dynamic, 2>&,
                                                           Eigen::Matrix<int, Eigen::Dynamic, 2>&,
                                                           bool strict = false);

    Eigen::Matrix<int, Eigen::Dynamic, 1> findCans(Eigen::Matrix<int, Eigen::Dynamic, 2>& ab,
                                                   Eigen::Matrix<int, Eigen::Dynamic, 2>& bc);

    bool isPairNew(int, int, Eigen::Matrix<int, Eigen::Dynamic, 2>&);

    bool isCanNew(int, Eigen::Matrix<int, Eigen::Dynamic, 1>&);

    rules::PairsOverWholeSky pairsOverWholeSky;
    stars::Image& image;
    double triTol;
    int triMaxCnt;
    int starsCnt;
    int triCur;
};

}

#endif
