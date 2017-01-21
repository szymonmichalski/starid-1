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

                double ab0 = std::acos( arma::dot( arma::trans( image.uvecs.row(i-1) ) , arma::trans( image.uvecs.row(j-1) ) ) );
                double ac0 = std::acos( arma::dot( arma::trans( image.uvecs.row(i-1) ) , arma::trans( image.uvecs.row(k-1) ) ) );
                double bc0 = std::acos( arma::dot( arma::trans( image.uvecs.row(j-1) ) , arma::trans( image.uvecs.row(k-1) ) ) );
                if ( std::abs( ab0 - ac0 ) < 10.0 * triTol ) continue;
                if ( std::abs( ab0 - bc0 ) < 10.0 * triTol ) continue;
                if ( std::abs( ac0 - bc0 ) < 10.0 * triTol ) continue;

                Eigen::Matrix<int, 1000, 2> ab = pairsOverWholeSky.pairsMatrix(ab0, 0.1 * triTol);
                Eigen::Matrix<int, 1000, 2> bc = pairsOverWholeSky.pairsMatrix(bc0, 0.1 * triTol);
                Eigen::Matrix<int, 1000, 2> cb = bc;
                Eigen::Matrix<int, 1000, 2> ac = pairsOverWholeSky.pairsMatrix(ac0, 0.1 * triTol);

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


