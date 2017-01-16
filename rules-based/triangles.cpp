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

        double ang_ab = std::acos( arma::dot( arma::trans(mata.row(triNdx)) , arma::trans(matb.row(triNdx)) ) );
        std::vector<int> ndxs_ab = pairsOverWholeSky.starsFromPairs(ang_ab, triTol);

        double ang_ac = std::acos( arma::dot( arma::trans(mata.row(triNdx)) , arma::trans(matc.row(triNdx)) ) );
        std::vector<int> ndxs_ac = pairsOverWholeSky.starsFromPairs(ang_ac, triTol);

        double ang_bc = std::acos( arma::dot( arma::trans(matb.row(triNdx)) , arma::trans(matc.row(triNdx)) ) );
        std::vector<int> ndxs_bc = pairsOverWholeSky.starsFromPairs(ang_bc, triTol);

        std::vector<int> ndxs_abac;
        std::set_intersection(ndxs_ab.begin(), ndxs_ab.end(), ndxs_ac.begin(), ndxs_ac.end(), back_inserter(ndxs_abac));

        for (auto ndx : ndxs_abac) candidateNdxs.push_back(ndx);
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


