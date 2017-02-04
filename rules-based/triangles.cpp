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
    int ndxi, ndxj, ndxk, dj, dk;
    triCur = 0;
    for (dj = 2; dj <= starsCnt-2; ++dj) {
        for (dk = 2; dk <= starsCnt-dj-1; ++dk) {
            for (ndxi = 2; ndxi <= starsCnt-dj-dk; ++ndxi) {
                ndxj = ndxi + dj;
                ndxk = ndxj + dk;
                arma::vec uveca = arma::trans(image.uvecs.row(0));
                arma::vec uvecb = arma::trans(image.uvecs.row(ndxi-1));
                arma::vec uvecc = arma::trans(image.uvecs.row(ndxj-1));
                arma::vec uvecd = arma::trans(image.uvecs.row(ndxk-1));
                std::vector<double> angs;
                angs.push_back(std::acos(arma::dot(uveca, uvecb)));
                angs.push_back(std::acos(arma::dot(uveca, uvecc)));
                angs.push_back(std::acos(arma::dot(uvecb, uvecc)));
                angs.push_back(std::acos(arma::dot(uvecd, uvecb)));
                angs.push_back(std::acos(arma::dot(uvecd, uvecc)));
                for (int ndx1 = 0; ndx1 < 5; ++ndx1) {
                    if (angs[ndx1] > stars::imageRadiusRadians) continue;
                    for (int ndx2 = ndx1+1; ndx2 < 5; ++ndx2) {
                        if (std::abs(angs[ndx1]-angs[ndx2]) < 4.0*tol_radius) continue;
                    }
                }
                std::unordered_multimap<int, int> ab = pairsOverWholeSky.pairsMap(angs[0], tol_radius);
                std::unordered_multimap<int, int> ac = pairsOverWholeSky.pairsMap(angs[1], tol_radius);
                std::unordered_multimap<int, int> bc = pairsOverWholeSky.pairsMap(angs[2], tol_radius);
                std::unordered_multimap<int, int> db = pairsOverWholeSky.pairsMap(angs[3], tol_radius);
                std::unordered_multimap<int, int> dc = pairsOverWholeSky.pairsMap(angs[4], tol_radius);
                constrainSide(bc, db, dc);
                constrainSide(bc, ab, ac);
                reduceSide(ab, bc);
                reduceSide(ac, bc);
                std::unordered_map<int, int> cans1 = findStarsInBothSides(ab, ac);

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

void rules::Triangles::reduceSide(std::unordered_multimap<int, int>& side,
                                  const std::unordered_multimap<int, int>& constr) {
    for (auto it1 = side.begin(); it1 != side.end(); ) {
        auto it2 = constr.find(it1->first);
        if (it2 == constr.end())
            it1 = side.erase(it1);
        else
            ++it1;
    }
}


void rules::Triangles::constrainSide(std::unordered_multimap<int, int>& side,
                                     const std::unordered_multimap<int, int>& constra,
                                     const std::unordered_multimap<int, int>& constrb) {
    for (auto it = side.begin(); it != side.end(); ) {
        auto ita = constra.find(it->first);
        auto itb = constrb.find(it->first);
        if (ita == constra.end() || itb == constrb.end())
            it = side.erase(it);
        else
            ++it;
    }
}


std::unordered_map<int,int> rules::Triangles::findStarsInBothSides(const std::unordered_multimap<int, int>& sidea,
                                                                   const std::unordered_multimap<int, int>& sideb) {
    std::unordered_map<int, int> cans;
    for (auto it = sidea.begin(), end = sidea.end(); it != end; ++it) {
        auto it2 = sideb.find(it->first);
        if (it2 != sideb.end()) {
            cans.emplace(it->first, 1);
        }
    }
    return cans;
}



