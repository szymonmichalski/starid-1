#ifndef TRIPLETS_H
#define TRIPLETS_H

#include "image.h"
#include "pairs_over_whole_sky.h"

namespace rules {

struct Triangle {
    arma::vec uva;
    arma::vec uvb;
    arma::vec uvc;
    double angab;
    double angac;
    double angbc;
};

class Triangles
{

public:

    Triangles(stars::Image& image,
              rules::PairsOverWholeSky& pairs,
              double triTol,
              int triMaxCnt);
    int identifyCentralStar();

private:

    rules::PairsOverWholeSky pairsOverWholeSky;
    stars::Image& image;
    double triTol;
    uint triMaxCnt;
    uint starsCnt;
    uint triCur;
};

}

#endif
