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
                if (abbc(0,0) == 0 || accb(0,0) == 0) continue;

                Eigen::Matrix<int, 1000, 2> constraint = findRelatedPairs(abbc, accb);
                if (constraint(0,0) == 0) continue;

                Eigen::Matrix<int, 1000, 2> bc = findRelatedPairs(abbc, constraint); // constrained
                Eigen::Matrix<int, 1000, 2> cb = findRelatedPairs(accb, constraint); // constrained
                if (bc(0,0) == 0 || cb(0,0) == 0) continue;

                Eigen::Matrix<int, 1000, 1> cans1 = findCandidates(abbc, bc); // constrained by bc
                Eigen::Matrix<int, 1000, 1> cans2 = findCandidates(accb, cb); // constrained by cb
                if (cans1(0,0) == 0 || cans2(0,0) == 0) continue;
                for (int ndx = 0; ndx < 1000; ++ndx) {
                    if (cans1(ndx,0) == 0) break;
                    candidateNdxs.push_back(cans1(ndx,0));
                }
                for (int ndx = 0; ndx < 1000; ++ndx) {
                    if (cans2(ndx,0) == 0) break;
                    candidateNdxs.push_back(cans2(ndx,0));
                }

                ++triCur;
                if (triCur == triMaxCnt-1) break;
            }
            if (triCur == triMaxCnt-1) break;
        }
        if (triCur == triMaxCnt-1) break;
    }

    int maxCnts = 0;
    int topNdx = -1;
    std::map<int,int> candidateCnts;
    for (auto it = candidateNdxs.begin(); it != candidateNdxs.end(); ++it) {
        candidateCnts[*it]++;
        if (candidateCnts[*it] > maxCnts) {
            maxCnts = candidateCnts[*it];
            topNdx = *it;
        }
    }
    return topNdx;
}

Eigen::Matrix<int, 1000, 2> rules::Triangles::findRelatedPairs(Eigen::Matrix<int, 1000, 2>& pairsa, Eigen::Matrix<int, 1000, 2>& pairsb) {
    Eigen::Matrix<int, 1000, 2> pairsc;
    pairsc.setZero();
    int ndxc = 0;
    for (int ndxa = 0; ndxa < 1000; ++ndxa) {
        if (pairsa(ndxa,0) == 0) break;
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

Eigen::Matrix<int, 1000, 1> rules::Triangles::findCandidates(Eigen::Matrix<int, 1000, 2>& pairsa, Eigen::Matrix<int, 1000, 2>& constraint) {
    Eigen::Matrix<int, 1000, 1> cans;
    cans.setZero();
    int cansndx = 0;
    for (int ndxa = 0; ndxa < 1000; ++ndxa) {
        if (pairsa(ndxa,0) == 0) break;
        for (int ndxb = 0; ndxb < 1000; ++ndxb) {
            if (constraint(ndxb,0) == 0) break;
            int can = 0;
            if (pairsa(ndxa,0) == constraint(ndxb,0) && pairsa(ndxa,1) != constraint(ndxb,1)) {
                can = pairsa(ndxa,1);
            } else if (pairsa(ndxa,0) != constraint(ndxb,0) && pairsa(ndxa,1) == constraint(ndxb,1)) {
                can = pairsa(ndxa,0);
            } else {
                continue;
            }
            if (isCanNew(can, cans)) {
                cans(cansndx,0) = can;
                ++cansndx;
            }
        }
    }
    return cans;
}

bool rules::Triangles::isPairNew(int int1, int int2, Eigen::Matrix<int, 1000, 2>& mat) {
    for (int ndx = 0; ndx < 1000; ++ndx) {
        if (mat(ndx,0) == 0) break;
        if (mat(ndx,0) == int1 && mat(ndx,1) == int2) return false;
        if (mat(ndx,1) == int1 && mat(ndx,0) == int2) return false;
    }
    return true;
}

bool rules::Triangles::isCanNew(int int1, Eigen::Matrix<int, 1000, 1>& mat) {
    for (int ndx = 0; ndx < 1000; ++ndx) {
        if (mat(ndx,0) == 0) break;
        if (mat(ndx,0) == int1) return false;
    }
    return true;
}
