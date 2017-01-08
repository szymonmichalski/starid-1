#include "triangles.h"
#include "stopwatch.h"
#include <map>

rules::Triangles::Triangles(stars::Image& image,
                            rules::PairsOverWholeSky& pairs,
                            double triTol,
                            int triMaxCnt) :
    pairsOverWholeSky(pairs),
    image(image),
    triTol(triTol),
    triMaxCnt(triMaxCnt),
    starsCnt(image.uvecs.n_rows),
    triCur(0)
{}

int rules::Triangles::identifyCentralStar() {
    double centerStarBound = 10 * (arma::datum::pi / 648e3); // ten arcseconds in radians
    arma::mat mata;
    arma::mat matb;
    arma::mat matc;
    mata.zeros(triMaxCnt,3);
    matb.zeros(triMaxCnt,3);
    matc.zeros(triMaxCnt,3);
    triCur = 0;
    uint i, j, k, dj, dk;
    for (dj = 1; dj <= starsCnt-2; ++dj) {
        for (dk = 1; dk <= starsCnt-dj-1; ++dk) {
            for (i = 1; i <= starsCnt-dj-dk; ++i) {
                j = i + dj;
                k = j + dk;
                double x = image.uvecs(i-1,0);
                double y = image.uvecs(i-1,1);
                double z = image.uvecs(i-1,2);
                double h = atan2(x, z);
                double v = atan2(y, z);
                // star a is at center of field of view
                if (abs(h) > centerStarBound || abs(v) > centerStarBound) continue;
                mata.row(triCur) = image.uvecs.row(i-1);
                matb.row(triCur) = image.uvecs.row(j-1);
                matc.row(triCur) = image.uvecs.row(k-1);
                ++triCur;
                if (triCur == triMaxCnt-1) break;
            }
            if (triCur == triMaxCnt-1) break;
        }
        if (triCur == triMaxCnt-1) break;
    }
    if (triCur < triMaxCnt-1) {
        mata.shed_rows(triCur,triMaxCnt-1);
        matb.shed_rows(triCur,triMaxCnt-1);
        matc.shed_rows(triCur,triMaxCnt-1);
    }
    std::vector<int> staraCandNdxs;
    for (uint i = 0; i < mata.n_rows; ++i) {
        rules::Triangle triangle;
        triangle.uva = arma::trans(mata.row(i));
        triangle.uvb = arma::trans(matb.row(i));
        triangle.uvc = arma::trans(matc.row(i));
        triangle.angab = acos(arma::dot(triangle.uva, triangle.uvb));
        triangle.angac = acos(arma::dot(triangle.uva, triangle.uvc));
        triangle.angbc = acos(arma::dot(triangle.uvb, triangle.uvc));
        // triangle sides are too similar
        if (std::abs(triangle.angab - triangle.angac) < triTol
            || std::abs(triangle.angab - triangle.angbc) < triTol
            || std::abs(triangle.angac - triangle.angbc) < triTol) continue;
        std::vector<int> l1ab = pairsOverWholeSky.starsFromPairs(triangle.angab, 0.05 * triTol);
        std::vector<int> l1ac = pairsOverWholeSky.starsFromPairs(triangle.angac, 0.05 * triTol);
        std::vector<int> l1bc = pairsOverWholeSky.starsFromPairs(triangle.angbc, 0.05 * triTol);
        std::vector<int> l2abac;
        std::vector<int> l2babc;
        std::vector<int> l2cacb;
        std::set_intersection(l1ab.begin(), l1ab.end(), l1ac.begin(), l1ac.end(), back_inserter(l2abac));
        std::set_intersection(l1ab.begin(), l1ab.end(), l1bc.begin(), l1bc.end(), back_inserter(l2babc));
        std::set_intersection(l1ac.begin(), l1ac.end(), l1bc.begin(), l1bc.end(), back_inserter(l2cacb));
        for (auto ndx : l2abac) staraCandNdxs.push_back(ndx);
    }
    int max = 0;
    int most_common = -1;
    std::map<int,int> m;
    for (auto it = staraCandNdxs.begin(); it != staraCandNdxs.end(); ++it) {
      m[*it]++;
      if (m[*it] > max) {
        max = m[*it];
        most_common = *it;
      }
    }
    return most_common;
}


