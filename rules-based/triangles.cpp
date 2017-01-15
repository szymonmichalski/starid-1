#include "triangles.h"
#include "stopwatch.h"
#include <map>
#include <cmath>

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
                if (i > 1) continue; // star a is center star
                j = i + dj;
                k = j + dk;
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
    std::vector<int> candidateNdxs;
    for (int triNdx = 0; triNdx < mata.n_rows; ++triNdx) {
        rules::Triangle triangle;
        triangle.uva = arma::trans(mata.row(triNdx));
        triangle.uvb = arma::trans(matb.row(triNdx));
        triangle.uvc = arma::trans(matc.row(triNdx));

        triangle.angab = std::acos( arma::dot(triangle.uva, triangle.uvb) );
        triangle.angac = std::acos( arma::dot(triangle.uva, triangle.uvc) );
        triangle.angbc = std::acos( arma::dot(triangle.uvb, triangle.uvc) );

        std::vector<int> l1ab = pairsOverWholeSky.starsFromPairs(triangle.angab, triTol);
        std::vector<int> l1ac = pairsOverWholeSky.starsFromPairs(triangle.angac, triTol);
        std::vector<int> l1bc = pairsOverWholeSky.starsFromPairs(triangle.angbc, triTol);

        std::vector<int> l2abac;
        std::vector<int> l2babc;
        std::vector<int> l2cacb;
        std::set_intersection(l1ab.begin(), l1ab.end(), l1ac.begin(), l1ac.end(), back_inserter(l2abac));
        std::set_intersection(l1ab.begin(), l1ab.end(), l1bc.begin(), l1bc.end(), back_inserter(l2babc));
        std::set_intersection(l1ac.begin(), l1ac.end(), l1bc.begin(), l1bc.end(), back_inserter(l2cacb));

        for (auto ndx : l2abac) candidateNdxs.push_back(ndx);
    }

    int maxCnts = 0;
    int mostCommonNdx = -1;
    std::map<int,int> candidateCnts;
    for (auto it = candidateNdxs.begin(); it != candidateNdxs.end(); ++it) {
      candidateCnts[*it]++;
      if (candidateCnts[*it] > maxCnts) {
        maxCnts = candidateCnts[*it];
        mostCommonNdx = *it;
      }
    }
    return mostCommonNdx;
}


