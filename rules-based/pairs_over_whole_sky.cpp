#include "pairs_over_whole_sky.h"
#include "globals.h"

void rules::PairsOverWholeSky::init(stars::Sky& sky)
{
    int pairndx = 0;
    for(auto star : sky.stars) {
        std::vector<int> neighborndxs = sky.starsNearPoint(star.x, star.y, star.z);
        for (auto neighborndx : neighborndxs) {
            if (star.starndx == neighborndx) continue;
            std::string key = pairsKey(star.starndx, sky.stars[neighborndx].starndx);
            auto search = starpairs_map.find(key);
            if (search != starpairs_map.end()) continue; // check map that pair is unique
            double angle = acos( (star.x * sky.stars[neighborndx].x)
                                 + (star.y * sky.stars[neighborndx].y)
                                 + (star.z * sky.stars[neighborndx].z));
            if (std::fabs(angle) > stars::imageRadiusRadians) continue;
            std::tuple<double, int, int> starpair {angle, star.starndx, neighborndx};
            starpairs.push_back(starpair);
            starpairs_map.insert({key, pairndx}); // update map of unique pairs
            angletable.addPair(angle, pairndx);
            ++pairndx;
        }
    }
    angletable.sort();
}

std::unordered_multimap<int, int> rules::PairsOverWholeSky::pairsMap(double angle, double tol_radius) {
    std::unordered_multimap<int, int> map;

    double ang1 = angle - tol_radius;
    if (ang1 <= 0) ang1 = 0;
    if (ang1 >= stars::imageRadiusRadians) ang1 = stars::imageRadiusRadians - (stars::imageRadiusRadians/28);

    double ang2 = angle + tol_radius;
    if (ang2 <= 0) ang2 = 0 + (stars::imageRadiusRadians/28);
    if (ang2 >= stars::imageRadiusRadians) ang2 = stars::imageRadiusRadians;

    if (ang1 >= ang2) ang1 = ang2 - (stars::imageRadiusRadians/28);

    std::vector<int> intsFromTable = angletable.findInts(ang1, ang2);
    for (auto ndx : intsFromTable) {
        map.emplace(std::get<1>(starpairs[ndx]), std::get<2>(starpairs[ndx]));
        map.emplace(std::get<2>(starpairs[ndx]), std::get<1>(starpairs[ndx]));
    }
    return map;
}


Eigen::Matrix<int, Eigen::Dynamic, 2> rules::PairsOverWholeSky::pairsMatrix(double angle, double tol_radius) {
    using namespace Eigen;
    Matrix<int, Dynamic, 2> pairsMat;
    pairsMat.resize(1000,2);
    pairsMat.setZero();

    double ang1 = angle - tol_radius;
    if (ang1 <= 0) ang1 = 0;
    if (ang1 >= stars::imageRadiusRadians) ang1 = stars::imageRadiusRadians - (stars::imageRadiusRadians/28);

    double ang2 = angle + tol_radius;
    if (ang2 <= 0) ang2 = 0 + (stars::imageRadiusRadians/28);
    if (ang2 >= stars::imageRadiusRadians) ang2 = stars::imageRadiusRadians;

    if (ang1 >= ang2) ang1 = ang2 - (stars::imageRadiusRadians/28);

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


std::vector<int> rules::PairsOverWholeSky::pairsVector(double angle, double tol_radius)
{
    std::vector<int> intsFromTable = angletable.findInts(angle-tol_radius, angle+tol_radius);
    std::vector<int> starndxs; // list of stars from the pairs
    for (auto pairndx : intsFromTable) {
        starndxs.push_back(std::get<1>(starpairs[pairndx]));
        starndxs.push_back(std::get<2>(starpairs[pairndx]));
    }
    std::sort(starndxs.begin(), starndxs.end());
    return starndxs;
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

void rules::PairsOverWholeSky::Status() {
}
