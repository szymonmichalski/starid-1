#include "triangles.h"

rules::Triangles::Triangles(stars::Image& image,
                            rules::PairsOverWholeSky& pairs,
                            double triTol,
                            int triMaxCnt) :
    pairsOverWholeSky(pairs),
    image(image),
    tol_radius(triTol),
    triMaxCnt(triMaxCnt),
    starsCnt(image.uvecs.n_rows),
    triCur(0)
{}

int rules::Triangles::identifyCentralStar() {
    using namespace Eigen;
    arma::mat mata;
    arma::mat matb;
    arma::mat matc;
    mata.zeros(triMaxCnt,3);
    matb.zeros(triMaxCnt,3);
    matc.zeros(triMaxCnt,3);

    std::unordered_map<int, int> cans;
    int i, j, k, dj, dk;
    triCur = 0;
    for (dj = 1; dj <= starsCnt-2; ++dj) {
        for (dk = 1; dk <= starsCnt-dj-1; ++dk) {
            for (i = 1; i <= starsCnt-dj-dk; ++i) {
                if (i != 1) continue; // center star
                j = i + dj;
                k = j + dk;

                double angab = std::acos( arma::dot( arma::trans( image.uvecs.row(i-1) ) , arma::trans( image.uvecs.row(j-1) ) ) );
                double angac = std::acos( arma::dot( arma::trans( image.uvecs.row(i-1) ) , arma::trans( image.uvecs.row(k-1) ) ) );
                double angbc = std::acos( arma::dot( arma::trans( image.uvecs.row(j-1) ) , arma::trans( image.uvecs.row(k-1) ) ) );
                if (angab >= stars::imageRadiusRadians) continue;
                if (angac >= stars::imageRadiusRadians) continue;
                if (angbc >= stars::imageRadiusRadians) continue;
                if ( std::abs( angab - angac ) < 2.0 * tol_radius ) continue;
                if ( std::abs( angab - angbc ) < 2.0 * tol_radius ) continue;
                if ( std::abs( angac - angbc ) < 2.0 * tol_radius ) continue;
                std::unordered_multimap<int, int> ab = pairsOverWholeSky.pairsMap(angab, tol_radius);
                std::unordered_multimap<int, int> ac = pairsOverWholeSky.pairsMap(angac, tol_radius);
                std::unordered_multimap<int, int> bc = pairsOverWholeSky.pairsMap(angbc, tol_radius);
                std::unordered_map<int, int> cansab = findCansFromTwoSides(ab, bc);
                std::unordered_map<int, int> cansac = findCansFromTwoSides(ac, bc);
                std::unordered_map<int, int> cansFromTwoSides;
                for (auto itab = cansab.begin(), end = cansab.end(); itab != end; ++itab) {
                    auto itac = cansac.find(itab->first);
                    if (itac != cansac.end()) {
                        cansFromTwoSides.emplace(itab->first, 1);
                    }
                }

                if (cans.empty()) {
                    cans = cansFromTwoSides;
                } else {
                    std::unordered_map<int, int> tmpcans;
                    for (auto it1 = cansFromTwoSides.begin(), end = cansFromTwoSides.end(); it1 != end; ++it1) {
                        auto itcan = cans.find(it1->first);
                        if (itcan != cans.end()) {
                            tmpcans.emplace(it1->first, itcan->second+1);
                        }
                    }
                    cans = tmpcans;
                }

                ++triCur;
                if (triCur == triMaxCnt-1) break;
            }
            if (triCur == triMaxCnt-1) break;
        }
        if (triCur == triMaxCnt-1) break;
    }
    int starndx = 0;
    int maxcnt = 0;
    for (auto itcan = cans.begin(), end = cans.end(); itcan != end; ++itcan) {
        if (itcan->second > maxcnt) {
            starndx = itcan->first;
            maxcnt = itcan->second;
        }
    }
    return starndx;
}

std::unordered_map<int,int> rules::Triangles::findCansFromTwoSides(std::unordered_multimap<int, int>& ab,
                                                                   std::unordered_multimap<int, int>& bc) {
    std::unordered_map<int, int> cans;
    for (auto itab = ab.begin(), end = ab.end(); itab != end; ++itab) {
        auto itbc = bc.find(itab->first);
        if (itbc != bc.end() && itbc->second != itab->second) {
            int can = itab->second;
            auto itcans = cans.find(can);
            if (itcans != cans.end()) {
                ++itcans->second;
                continue;
            }
            cans.emplace(can, 1);
        }
    }
    return cans;
}



