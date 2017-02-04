#include "triangles.h"

rules::Triangles::Triangles(stars::Image& image,
                            rules::PairsOverWholeSky& pairs,
                            double tolrad,
                            int triMaxCnt) :
    pairsOverWholeSky(pairs),
    image(image),
    tol_radius(tolrad),
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

                std::vector<double> angs;
                angs.push_back(std::acos(arma::dot(uveca, uvecb)));
                angs.push_back(std::acos(arma::dot(uveca, uvecc)));
                angs.push_back(std::acos(arma::dot(uvecb, uvecc)));
                angs.push_back(std::acos(arma::dot(uvecd, uvecb)));
                angs.push_back(std::acos(arma::dot(uvecd, uvecc)));
                for (int i = 0; i < 5; ++i) {
                    if (angs[i] > stars::imageRadiusRadians) continue;
                    for (int j = i+1; j < 5; ++j) {
                        if (std::abs(angs[i]-angs[j]) < 4.0*tol_radius) continue;
                    }
                }

                std::unordered_multimap<int, int> ab = pairsOverWholeSky.pairsMap(angs[0], tol_radius);
                std::unordered_multimap<int, int> ac = pairsOverWholeSky.pairsMap(angs[1], tol_radius);
                std::unordered_multimap<int, int> bc = pairsOverWholeSky.pairsMap(angs[2], tol_radius);
                std::unordered_multimap<int, int> db = pairsOverWholeSky.pairsMap(angs[3], tol_radius);
                std::unordered_multimap<int, int> dc = pairsOverWholeSky.pairsMap(angs[4], tol_radius);

                constrainSide(bc, ab, ac);
                constrainSide(bc, db, dc);

                std::unordered_map<int, int> cansdb = findCansFromTwoSides(db, bc);
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

void rules::Triangles::constrainSide(std::unordered_multimap<int, int>& side,
                                     const std::unordered_multimap<int, int>& cona,
                                     const std::unordered_multimap<int, int>& conb) {

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



