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

    Triangles(stars::Image& image,
              rules::PairsOverWholeSky& pairs,
              double tol_radius,
              int triMaxCnt);

    int identifyCentralStar();

private:

    Eigen::Matrix<int, Eigen::Dynamic, 2> findRelatedPairs(Eigen::Matrix<int, Eigen::Dynamic, 2>&,
                                                           Eigen::Matrix<int, Eigen::Dynamic, 2>&,
                                                           bool strict = false);

    Eigen::Matrix<int, Eigen::Dynamic, 1> findCans(Eigen::Matrix<int, Eigen::Dynamic, 2>& ab,
                                                   Eigen::Matrix<int, Eigen::Dynamic, 2>& bc);

    Eigen::Matrix<int, Eigen::Dynamic, 1> findCans(Eigen::Matrix<int, Eigen::Dynamic, 2>& ab,
                                                   std::unordered_multimap<int, int>& bc);

    std::unordered_map<int,int> findCans2(Eigen::Matrix<int, Eigen::Dynamic, 2>& ab,
                                         std::unordered_multimap<int, int>& bc);

    bool isPairNew(int, int, Eigen::Matrix<int, Eigen::Dynamic, 2>&);

    bool isCanNew(int, Eigen::Matrix<int, Eigen::Dynamic, 1>&);

    rules::PairsOverWholeSky pairsOverWholeSky;
    stars::Image& image;
    double tol_radius;
    int triMaxCnt;
    int starsCnt;
    int triCur;
};

}

#endif
