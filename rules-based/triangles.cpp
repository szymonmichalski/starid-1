#include "triangles.h"

rules::Triangles::Triangles(stars::Image& image, rules::PairsOverWholeSky& pairs, double tolrad) :
    pairsOverWholeSky(pairs), image(image), tol_radius(tolrad) {
}

int rules::Triangles::identifyCentralStar() {
    using namespace Eigen;
    std::unordered_map<int, int> curstars;
    int starsCnt = image.uvecs.n_rows;
    int ndxi, ndxj, ndxk, dj, dk;

    for (dj = 2; dj <= starsCnt-2; ++dj) {
        for (dk = 2; dk <= starsCnt-dj-1; ++dk) {
            for (ndxi = 2; ndxi <= starsCnt-dj-dk; ++ndxi) {
                ndxj = ndxi + dj;
                ndxk = ndxj + dk;

                std::vector<double> angs;
                arma::vec uveca = arma::trans(image.uvecs.row(0));
                arma::vec uvecb = arma::trans(image.uvecs.row(ndxi-1));
                arma::vec uvecc = arma::trans(image.uvecs.row(ndxj-1));
                arma::vec uvecd = arma::trans(image.uvecs.row(ndxk-1));
                angs.push_back(std::acos(arma::dot(uveca, uvecb)));
                angs.push_back(std::acos(arma::dot(uvecb, uvecc)));
                angs.push_back(std::acos(arma::dot(uvecc, uveca)));

                bool skip = false;
                for (int ndx1 = 0; ndx1 < 3; ++ndx1) {
                    if (angs[ndx1] > stars::maxStarPairAngle)
                        skip = true;
                }
                for (int ndx1 = 0; ndx1 < 3; ++ndx1) {
                    for (int ndx2 = ndx1; ndx2 < 3; ++ndx2) {
                        if (ndx1 == ndx2) continue;
                        if (std::abs(angs[ndx1]-angs[ndx2]) < 3000.0 * M_PI / 648000.0)
                            skip = true;
                    }
                }
                if (skip) continue;

                Triangle abc(angs[0], angs[1], angs[2], tol_radius, pairsOverWholeSky);

                std::unordered_map<int, int> merged; // = ad.stars_in_three_sides(ab, ac);
                update_stars(curstars, merged);
            }
        }
    }

    std::map<int, int> starsa;
    std::multimap<int, int, std::greater<int>> starsb;
    for (auto it = curstars.begin(), end = curstars.end(); it != end; ++it) {
        starsa.emplace(it->first, it->second);
        starsb.emplace(it->second, it->first);
    }
    return -1;
}

void rules::Triangles::update_stars(std::unordered_map<int, int>& stars1, const std::unordered_map<int, int>& stars2){
    for (auto it2 = stars2.begin(), end = stars2.end(); it2 != end; ++it2) {
        auto it1 = stars1.find(it2->first);
        if (it1 != stars1.end()) {
            ++it1->second;
        } else {
            stars1.emplace(it2->first, 1);
        }
    }
}





