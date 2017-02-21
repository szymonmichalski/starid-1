#include "pairs_over_whole_sky.h"
#include "globals.h"

void rules::PairsOverWholeSky::init(double max_ang, stars::Sky& sky)
{
    int pairndx = 0;
    for(auto star : sky.stars) {
        std::vector<int> neighborndxs = sky.starsNearPoint(star.x, star.y, star.z);
        for (auto neighborndx : neighborndxs) {
            if (star.starndx == neighborndx) continue;
            std::string key = pairsKey(star.starndx, sky.stars[neighborndx].starndx);
            auto search = starpairs_map.find(key);
            if (search != starpairs_map.end()) continue; // check map that pair is unique
            double angle = std::acos( (star.x * sky.stars[neighborndx].x)
                                 + (star.y * sky.stars[neighborndx].y)
                                 + (star.z * sky.stars[neighborndx].z));
            if (std::abs(angle) > max_ang) continue; // max pair angle

            std::tuple<double, int, int> starpair {angle, star.starndx, neighborndx};
            starpairs.push_back(starpair);
            starpairs_map.insert({key, pairndx}); // update map of unique pairs
            angletable.addPair(angle, pairndx);
            ++pairndx;
        }
    }
    angletable.sort();
}

std::unordered_map<int, std::unordered_map<int, int>> rules::PairsOverWholeSky::pairs_map(double angle, double tol_radius) {
    std::unordered_map<int, std::unordered_map<int, int>> stars;

    double ang1 = angle - tol_radius;
    double ang2 = angle + tol_radius;

    if (ang1 <= 0) ang1 = 0;
    if (ang2 <= 2.0 * tol_radius) ang2 = 2.0 * tol_radius;

    if (ang1 >= stars::image_radius_radians - 2.0 * tol_radius) ang1 = stars::image_radius_radians - 2.0 * tol_radius;
    if (ang2 >= stars::image_radius_radians) ang2 = stars::image_radius_radians;

    std::vector<int> intsFromTable = angletable.findInts(ang1, ang2);
    for (auto ndx : intsFromTable) {
        int star1 = std::get<1>(starpairs[ndx]);
        int star2 = std::get<2>(starpairs[ndx]);
        auto it1 = stars.find(star1);
        if (it1 != stars.end()) {
            auto &pairs1 = it1->second;
            pairs1.emplace(std::make_pair(star2,0)); // initial value for pair star key is 0
        } else {
            std::unordered_map<int, int> pairs1;
            pairs1.emplace(std::make_pair(star2,1));
            stars.emplace(std::make_pair(star1,pairs1));
        }
        auto it2 = stars.find(star2);
        if (it2 != stars.end()) {
            auto &pairs2 = it2->second;
            pairs2.emplace(std::make_pair(star1,0)); // initial value for pair star key is 0
        } else {
            std::unordered_map<int, int> pairs2;
            pairs2.emplace(std::make_pair(star1,1));
            stars.emplace(std::make_pair(star2,pairs2));
        }
    }

    return stars;
};

Eigen::Matrix<int, Eigen::Dynamic, 2> rules::PairsOverWholeSky::pairs_matrix(double angle, double tol_radius) {
    using namespace Eigen;
    Matrix<int, Dynamic, 2> pairsMat;
    pairsMat.resize(1000,2);
    pairsMat.setZero();

    double ang1 = angle - tol_radius;
    if (ang1 <= 0) ang1 = 0;
    if (ang1 >= stars::image_radius_radians) ang1 = stars::image_radius_radians - (stars::image_radius_radians/28);

    double ang2 = angle + tol_radius;
    if (ang2 <= 0) ang2 = 0 + (stars::image_radius_radians/28);
    if (ang2 >= stars::image_radius_radians) ang2 = stars::image_radius_radians;

    if (ang1 >= ang2) ang1 = ang2 - (stars::image_radius_radians/28);

    std::vector<int> intsFromTable = angletable.findInts(ang1, ang2);
    int pairsndx = 0;
    for (auto ndx : intsFromTable) {
        if (pairsMat.rows() < pairsndx+1) {
            pairsMat.conservativeResize(pairsMat.rows()+1000, pairsMat.cols());
            for (int i = pairsMat.rows() - 1000; i < pairsMat.rows(); ++i) {
                pairsMat(i,0) = 0;
                pairsMat(i,1) = 0;
            }
        }
        pairsMat(pairsndx,0) = (std::get<1>(starpairs[ndx]));
        pairsMat(pairsndx,1) = (std::get<2>(starpairs[ndx]));
        ++pairsndx;
    }
    return pairsMat;
}

std::string rules::PairsOverWholeSky::pairsKey(int catndx1, int catndx2) {
    if (catndx1 > catndx2) {
        int tmp = catndx1;
        catndx1 = catndx2;
        catndx2 = tmp;
    }
    std::string key = std::to_string(catndx1) + std::to_string(catndx2);
    return key;
}

void rules::PairsOverWholeSky::status() {
}
