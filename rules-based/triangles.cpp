#include "triangles.h"

rules::Triangles::Triangles(stars::Image& image, rules::PairsOverWholeSky& pairs, double tolrad, int triMaxCnt) :
    pairsOverWholeSky(pairs), image(image), tol_radius(tolrad), triMaxCnt(triMaxCnt) {
}

int rules::Triangles::identifyCentralStar() {
    using namespace Eigen;
    std::unordered_map<int, int> cans;
    int starsCnt = image.uvecs.n_rows;
    int ndxi, ndxj, ndxk, dj, dk;
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
                angs.push_back(std::acos(arma::dot(uvecd, uvecb)));
                angs.push_back(std::acos(arma::dot(uvecd, uvecc)));
                angs.push_back(std::acos(arma::dot(uvecb, uvecc)));
                angs.push_back(std::acos(arma::dot(uveca, uvecd)));

                bool skipThisTriangle = false;
                for (int ndx1 = 0; ndx1 < 6; ++ndx1) {
                    if (angs[ndx1] > stars::imageRadiusRadians) continue;
                    for (int ndx2 = ndx1+1; ndx2 < 6; ++ndx2) {
                        if (std::abs(angs[ndx1]-angs[ndx2]) < 4000.0 * (M_PI / 648000.0)) skipThisTriangle = true;
                    }
                }
                if (skipThisTriangle) continue;

                std::unordered_multimap<int, int> ab = pairsOverWholeSky.pairsMap(angs[0], tol_radius);
                std::unordered_multimap<int, int> ac = pairsOverWholeSky.pairsMap(angs[1], tol_radius);
                std::unordered_multimap<int, int> db = pairsOverWholeSky.pairsMap(angs[2], tol_radius);
                std::unordered_multimap<int, int> dc = pairsOverWholeSky.pairsMap(angs[3], tol_radius);
                std::unordered_multimap<int, int> bc = pairsOverWholeSky.pairsMap(angs[4], tol_radius);
                std::unordered_multimap<int, int> ad = pairsOverWholeSky.pairsMap(angs[5], tol_radius);

                constrainSide(ad, ab, db);
                constrainSide(ad, ac, dc);
                reduceSide(ab, ad);
                reduceSide(db, ad);
                reduceSide(ac, ad);
                reduceSide(dc, ad);

                constrainSide(bc, db, dc);
                constrainSide(bc, ab, ac);
                reduceSide(ab, bc);
                reduceSide(db, bc);
                reduceSide(ac, bc);
                reduceSide(dc, bc);

                std::unordered_map<int, int> stars = starsInThreeSides(ab, ac, ad);
                mergeStars(cans, stars);
            }
        }
    }

    std::map<int, int> cans1;
    std::multimap<int, int, std::greater<int>> cans2;
    for (auto it = cans.begin(), end = cans.end(); it != end; ++it) {
        cans1.emplace(it->first, it->second);
        cans2.emplace(it->second, it->first);
    }
    return 0;
}

void rules::Triangles::mergeStars(std::unordered_map<int, int>& stars1, const std::unordered_map<int, int>& stars2){
    for (auto it2 = stars2.begin(), end = stars2.end(); it2 != end; ++it2) {
        auto it1 = stars1.find(it2->first);
        if (it1 != stars1.end()) {
            ++it1->second;
        } else {
            stars1.emplace(it2->first, 1);
        }
    }
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

std::unordered_map<int,int> rules::Triangles::starsInThreeSides(const std::unordered_multimap<int, int>& sidea,
                                                                const std::unordered_multimap<int, int>& sideb,
                                                                const std::unordered_multimap<int, int>& sidec) {
    std::unordered_map<int, int> stars;
    for (auto it = sidea.begin(), end = sidea.end(); it != end; ++it) {
        auto it2 = sideb.find(it->first);
        if (it2 == sideb.end()) continue;
        auto it3 = sidec.find(it->first);
        if (it3 == sidec.end()) continue;
        stars.emplace(it->first, 1);
    }
    return stars;
}


std::unordered_map<int,int> rules::Triangles::starsInTwoSides(const std::unordered_multimap<int, int>& sidea,
                                                              const std::unordered_multimap<int, int>& sideb) {
    std::unordered_map<int, int> stars;
    for (auto it = sidea.begin(), end = sidea.end(); it != end; ++it) {
        auto it2 = sideb.find(it->first);
        if (it2 == sideb.end()) continue;
        stars.emplace(it->first, 1);
    }
    return stars;
}



