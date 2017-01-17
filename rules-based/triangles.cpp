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

    int i, j, k, dj, dk;
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
    for (int triNdx = 0; triNdx < (int)mata.n_rows; ++triNdx) {

        double ab0 = std::acos( arma::dot( arma::trans(mata.row(triNdx)) , arma::trans(matb.row(triNdx)) ) );
        double ac0 = std::acos( arma::dot( arma::trans(mata.row(triNdx)) , arma::trans(matc.row(triNdx)) ) );
        double bc0 = std::acos( arma::dot( arma::trans(matb.row(triNdx)) , arma::trans(matc.row(triNdx)) ) );
        if ( std::abs( ab0 - ac0 ) < 10.0 * triTol ) continue;
        if ( std::abs( ab0 - bc0 ) < 10.0 * triTol ) continue;
        if ( std::abs( ac0 - bc0 ) < 10.0 * triTol ) continue;

        std::vector<int> ab = pairsOverWholeSky.starsFromPairs(ab0, 0.1 * triTol);
        std::vector<int> ac = pairsOverWholeSky.starsFromPairs(ac0, 0.1 * triTol);
        std::vector<int> bc = pairsOverWholeSky.starsFromPairs(bc0, 0.1 * triTol);

        std::vector<int> abac;
        std::set_intersection(ab.begin(), ab.end(), ac.begin(), ac.end(), back_inserter(abac));
        std::vector<int> abbc;
        std::set_intersection(ab.begin(), ab.end(), bc.begin(), bc.end(), back_inserter(abbc));
        std::vector<int> acbc;
        std::set_intersection(ac.begin(), ac.end(), bc.begin(), bc.end(), back_inserter(acbc));
        std::vector<int> abbcacbc;
        std::set_intersection(abbc.begin(), abbc.end(), acbc.begin(), acbc.end(), back_inserter(abbcacbc));
        std::vector<int> abaconly;
        std::set_difference(abac.begin(), abac.end(), abbcacbc.begin(), abbcacbc.end(), back_inserter(abaconly));

        for (auto ndx : abaconly) candidateNdxs.push_back(ndx);
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


