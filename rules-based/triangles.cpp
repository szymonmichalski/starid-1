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

    std::vector<int> candidateNdxs;
    int i, j, k, dj, dk;
    triCur = 0;
    for (dj = 1; dj <= starsCnt-2; ++dj) {
        for (dk = 1; dk <= starsCnt-dj-1; ++dk) {
            for (i = 1; i <= starsCnt-dj-dk; ++i) {
                if (i != 1) continue; // star a is center star
                j = i + dj;
                k = j + dk;

                double angab = std::acos( arma::dot( arma::trans( image.uvecs.row(i-1) ) , arma::trans( image.uvecs.row(j-1) ) ) );
                double angac = std::acos( arma::dot( arma::trans( image.uvecs.row(i-1) ) , arma::trans( image.uvecs.row(k-1) ) ) );
                double angbc = std::acos( arma::dot( arma::trans( image.uvecs.row(j-1) ) , arma::trans( image.uvecs.row(k-1) ) ) );
                if ( std::abs( angab - angac ) < 10.0 * triTol ) continue;
                if ( std::abs( angab - angbc ) < 10.0 * triTol ) continue;
                if ( std::abs( angac - angbc ) < 10.0 * triTol ) continue;

                Eigen::Matrix<int, 1000, 2> tmp1 = pairsOverWholeSky.pairsMatrix(angab, 0.1 * triTol);
                Eigen::Matrix<int, 1000, 2> tmp2 = pairsOverWholeSky.pairsMatrix(angbc, 0.1 * triTol);
                Eigen::Matrix<int, 1000, 2> tmp3 = pairsOverWholeSky.pairsMatrix(angac, 0.1 * triTol);

                Eigen::Matrix<int, 1000, 2> abbc = findRelatedPairs(tmp1, tmp2);
                Eigen::Matrix<int, 1000, 2> accb = findRelatedPairs(tmp3, tmp2);

                ++triCur;
                if (triCur == triMaxCnt-1) break;
            }
            if (triCur == triMaxCnt-1) break;
        }
        if (triCur == triMaxCnt-1) break;
    }

    int topNdx = -1;
    return topNdx;
}

Eigen::Matrix<int, 1000, 2> rules::Triangles::findRelatedPairs(Eigen::Matrix<int, 1000, 2>& pairsa,
                                                               Eigen::Matrix<int, 1000, 2>& pairsb)
{
    Eigen::Matrix<int, 1000, 2> pairsc;
    pairsc.setZero();
    int ndxc = 0;
    for (int ndxa = 0; ndxa < 1000; ++ndxa) {
        if (pairsa(ndxa,0) == 0) break;
        // if either star from apair is in a bpair, add unique pairs to pairsc
        for (int ndxb = 0; ndxb < 1000; ++ndxb) {
            if (pairsb(ndxb,0) == 0) break;
            bool pairsAreRelated = false;
            bool pairsAreTheSame = false;
            bool apairIsNew = false;
            bool bpairIsNew = false;
            if (pairsa(ndxa,0) == pairsb(ndxb,0) || pairsa(ndxa,0) == pairsb(ndxb,1))
                pairsAreRelated = true;
            if (pairsa(ndxa,1) == pairsb(ndxb,0) || pairsa(ndxa,1) == pairsb(ndxb,1))
                pairsAreRelated = true;
            if (pairsa(ndxa,0) == pairsb(ndxb,0) && pairsa(ndxa,1) == pairsb(ndxb,1))
                pairsAreTheSame = true;
            if (pairsa(ndxa,1) == pairsb(ndxb,0) && pairsa(ndxa,0) == pairsb(ndxb,1))
                pairsAreTheSame = true;
            if (pairsAreRelated)
                apairIsNew = isPairNew(pairsa(ndxa,0), pairsa(ndxa,1), pairsc);
            if (pairsAreRelated && !pairsAreTheSame)
                bpairIsNew = isPairNew(pairsb(ndxb,0), pairsb(ndxb,1), pairsc);
            if (pairsAreRelated && pairsAreTheSame && apairIsNew) {
                pairsc(ndxc,0) = pairsa(ndxa,0);
                pairsc(ndxc,1) = pairsa(ndxa,1);
                ++ndxc;
            }
            if (pairsAreRelated && !pairsAreTheSame && apairIsNew) {
                pairsc(ndxc,0) = pairsa(ndxa,0);
                pairsc(ndxc,1) = pairsa(ndxa,1);
                ++ndxc;
            }
            if (pairsAreRelated && !pairsAreTheSame && bpairIsNew) {
                pairsc(ndxc,0) = pairsb(ndxb,0);
                pairsc(ndxc,1) = pairsb(ndxb,1);
                ++ndxc;
            }
        }
    }
    return pairsc;
}

bool rules::Triangles::isPairNew(int int1, int int2, Eigen::Matrix<int, 1000, 2>& mat) {
    for (int ndx = 0; ndx < 1000; ++ndx) {
        if (mat(ndx,0) == 0) break;
        if (mat(ndx,0) == int1 && mat(ndx,1) == int2) return false;
        if (mat(ndx,1) == int1 && mat(ndx,0) == int2) return false;
    }
    return true;
}

