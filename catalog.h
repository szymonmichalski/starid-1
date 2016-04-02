#ifndef CATALOG_H
#define CATALOG_H

#include "util.h"
#include "indexfinder.h"
#include <string>
#include <vector>

namespace catalog {

struct Star {
    std::string iau_identifier {""};
    std::string star_name {""};
    std::string variablestar_name {""};
    int skymap_number {0};
    int hd_number {0};
    int sao_number {0};
    int dm_number {0};
    int hr_number {0};
    int wds_number {0};
    int ppm_number {0};
    bool blended_position {false};
    double mv1 {100.0};
    double ra_degrees {0.0};
    double dec_degrees {0.0};
    util::UnitVector uvec;
};

class Catalog {
public:
    Catalog(const std::string& catalog_file, double years_from_j2000=0.0, double max_mv=7.2);
    std::vector<catalog::Star> stars;
    std::vector<int> StarsNearPoint(util::UnitVector& uvec, const double radius);
private:
    indexfinder::IndexFinder xfinder;
    indexfinder::IndexFinder yfinder;
    indexfinder::IndexFinder zfinder;
    std::vector<std::pair<double,int>> xtable;
    std::vector<std::pair<double,int>> ytable;
    std::vector<std::pair<double,int>> ztable;
    std::vector<int> StarsInRing(double p, double radius, indexfinder::IndexFinder& finder);
};

}

#endif
