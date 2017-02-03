#include "triangles.h"

rules::Triangles::Triangles(stars::Image& image,
                            rules::PairsOverWholeSky& pairs,
                            double triTol,
                            int triMaxCnt) :
    pairsOverWholeSky(pairs),
    image(image),
    tri_tol(triTol),
    triMaxCnt(triMaxCnt),
    starsCnt(image.uvecs.n_rows),
    triCur(0)
{}

int rules::Triangles::identifyCentralStar() {
    using namespace Eigen;
    std::unordered_map<int, int> cans;
    int i, j, k, dj, dk;
    triCur = 0;
    for (dj = 2; dj <= starsCnt-2; ++dj) {
        for (dk = 2; dk <= starsCnt-dj-1; ++dk) {
            for (i = 2; i <= starsCnt-dj-dk; ++i) {
                j = i + dj;
                k = j + dk;

                arma::vec uveca = arma::trans(image.uvecs.row(0));
                arma::vec uvecb = arma::trans(image.uvecs.row(i-1));
                arma::vec uvecc = arma::trans(image.uvecs.row(j-1));
                arma::vec uvecd = arma::trans(image.uvecs.row(k-1));
                double angab = std::acos(arma::dot(uveca, uvecb));
                double angac = std::acos(arma::dot(uveca, uvecc));
                double angbc = std::acos(arma::dot(uvecb, uvecc));
                double angdb = std::acos(arma::dot(uvecd, uvecb));
                double angdc = std::acos(arma::dot(uvecd, uvecc));
                if (angab >= stars::imageRadiusRadians) continue;
                if (angac >= stars::imageRadiusRadians) continue;
                if (angbc >= stars::imageRadiusRadians) continue;
                if (angdb >= stars::imageRadiusRadians) continue;
                if (angdc >= stars::imageRadiusRadians) continue;
                if (std::abs(angab - angac) < tri_tol ) continue;
                if (std::abs(angdb - angdc) < tri_tol ) continue;

                std::unordered_multimap<int, int> ab = pairsOverWholeSky.pairsMap(angab, tri_tol);
                std::unordered_multimap<int, int> ac = pairsOverWholeSky.pairsMap(angac, tri_tol);
                std::unordered_multimap<int, int> bc = pairsOverWholeSky.pairsMap(angbc, tri_tol);
                std::unordered_multimap<int, int> db = pairsOverWholeSky.pairsMap(angdb, tri_tol);
                std::unordered_multimap<int, int> dc = pairsOverWholeSky.pairsMap(angdc, tri_tol);

                std::unordered_map<int, int> cansdb = findCansFromTwoSides(db, bc); // constrain bc
                std::unordered_map<int, int> cansdc = findCansFromTwoSides(dc, bc);

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



