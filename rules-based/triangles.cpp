#include "triangles.h"
#include "triangle_side.h"

rules::Triangles::Triangles(stars::Image& image, rules::PairsOverWholeSky& pairs, double tolrad) :
    pairsOverWholeSky(pairs), image(image), tol_radius(tolrad) {
}

int rules::Triangles::identifyCentralStar() {
    using namespace Eigen;
    std::unordered_map<int, int> stars;
    int starsCnt = image.uvecs.n_rows;
    int ndxi, ndxj, ndxk, dj, dk;
    arma::vec uveca = arma::trans(image.uvecs.row(0));

    for (dj = 2; dj <= starsCnt-2; ++dj) {
        for (dk = 2; dk <= starsCnt-dj-1; ++dk) {
            for (ndxi = 2; ndxi <= starsCnt-dj-dk; ++ndxi) {
                ndxj = ndxi + dj;
                ndxk = ndxj + dk;

                std::vector<double> angs;
                arma::vec uvecb = arma::trans(image.uvecs.row(ndxi-1));
                arma::vec uvecc = arma::trans(image.uvecs.row(ndxj-1));
                arma::vec uvecd = arma::trans(image.uvecs.row(ndxk-1));
                angs.push_back(std::acos(arma::dot(uveca, uvecb)));
                angs.push_back(std::acos(arma::dot(uveca, uvecc)));
                angs.push_back(std::acos(arma::dot(uvecd, uvecb)));
                angs.push_back(std::acos(arma::dot(uvecd, uvecc)));
                angs.push_back(std::acos(arma::dot(uvecb, uvecc)));
                angs.push_back(std::acos(arma::dot(uveca, uvecd)));

                bool skipThisTriangle = false;
                for (int ndx1 = 0; ndx1 < 6; ++ndx1) {
                    if (angs[ndx1] > stars::imageRadiusRadians) skipThisTriangle = true;
                    for (int ndx2 = ndx1+1; ndx2 < 6; ++ndx2) {
                        if (std::abs(angs[ndx1]-angs[ndx2]) < 500.0 * M_PI / 648000.0) skipThisTriangle = true;
                    }
                }
                if (skipThisTriangle) continue;

                rules::TriangleSide test(angs[0], tol_radius, pairsOverWholeSky);
                std::map<int, int> test2 = test.status();

                std::unordered_multimap<int, int> ab = pairsOverWholeSky.pairsMap(angs[0], tol_radius);
                std::unordered_multimap<int, int> ac = pairsOverWholeSky.pairsMap(angs[1], tol_radius);
                std::unordered_multimap<int, int> db = pairsOverWholeSky.pairsMap(angs[2], tol_radius);
                std::unordered_multimap<int, int> dc = pairsOverWholeSky.pairsMap(angs[3], tol_radius);
                std::unordered_multimap<int, int> bc = pairsOverWholeSky.pairsMap(angs[4], tol_radius);
                std::unordered_multimap<int, int> ad = pairsOverWholeSky.pairsMap(angs[5], tol_radius);

                std::vector<int> cntbc;
                std::vector<int> cntad;
                std::vector<int> cntab;
                std::vector<int> cntac;
                cntbc.push_back(bc.size());
                cntad.push_back(ad.size());
                cntab.push_back(ab.size());
                cntac.push_back(ac.size());
                for (int redndx = 1; redndx < 5; ++redndx) {
                    constraint(bc, ab, db, ac, dc);
                    reduce2(ab, ac, bc);
                    reduce2(ac, ab, bc);
                    reduce2(db, dc, bc);
                    reduce2(dc, db, bc);
                    constraint(ad, db, dc, ab, ac);
                    reduce2(db, ab, ad);
                    reduce2(ac, db, ad);
                    reduce2(dc, ac, ad);
                    reduce2(ac, dc, ad);
                    cntbc.push_back(bc.size());
                    cntad.push_back(ad.size());
                    cntab.push_back(ab.size());
                    cntac.push_back(ac.size());
                }

                std::unordered_map<int, int> starstmp = starsInThreeSides(ab, ac, ad);
                mergeStars(stars, starstmp);
            }
        }
    }

    std::map<int, int> starsa;
    std::multimap<int, int, std::greater<int>> starsb;
    for (auto it = stars.begin(), end = stars.end(); it != end; ++it) {
        starsa.emplace(it->first, it->second);
        starsb.emplace(it->second, it->first);
    }
    return -1;
}

void rules::Triangles::reduce2(
        std::unordered_multimap<int, int>& side,
        const std::unordered_multimap<int, int>& side2,
        const std::unordered_multimap<int, int>& con) {
    for (auto it = side.begin(); it != side.end(); ) {
        ++it;
    }
}

void rules::Triangles::constraint(std::unordered_multimap<int, int>& side, // picture bc case
                                  const std::unordered_multimap<int, int>& ll, // left lower
                                  const std::unordered_multimap<int, int>& lu, // left upper
                                  const std::unordered_multimap<int, int>& rl, // right lower
                                  const std::unordered_multimap<int, int>& ru // right upper
                                  ) {
    for (auto it = side.begin(); it != side.end(); ) {
        auto ll1 = ll.find(it->first);
        auto lu1 = lu.find(it->first);
        auto rl1 = rl.find(it->first);
        auto ru1 = ru.find(it->first);
        auto ll2 = ll.find(it->second);
        auto lu2 = lu.find(it->second);
        auto rl2 = rl.find(it->second);
        auto ru2 = ru.find(it->second);
        if ( ((ll1 != ll.end() && lu1 != lu.end()) && (rl2 != rl.end() && ru2 != ru.end())) ||
             ((ll2 != ll.end() && lu2 != lu.end()) && (rl1 != rl.end() && ru1 != ru.end())) )
            ++it;
        else
            it = side.erase(it);
    }
}

void rules::Triangles::reduce1(std::unordered_multimap<int, int>& side,
                               const std::unordered_multimap<int, int>& side2) {
    for (auto it = side.begin(); it != side.end(); ) {
        auto it2a = side2.find(it->first);
        auto it2b = side2.find(it->second);
        if ( it2a != side2.end() || it2b != side2.end() )
            ++it;
        else
            it = side.erase(it);
    }
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



