#ifndef CATALOG_H
#define CATALOG_H

#include "geometry.h"
#include "indexfinder.h"
#include <string>
#include <vector>

namespace catalog {

struct Star {
    std::string iau_identifier;
    std::string star_name;
    std::string variablestar_name;
    int skymap_number;
    int hd_number;
    int sao_number;
    int dm_number;
    int hr_number;
    int wds_number;
    int ppm_number;
    bool blended_position;
    double mv1;
    double ra_degrees;
    double dec_degrees;
    geometry::UnitVector uvec;
    Star();
};

class Catalog {
public:
    Catalog(const std::string& catalog_file, double j2koffset, double mv);
    std::vector<catalog::Star> stars;
    std::vector<int> StarsNearPoint(geometry::UnitVector& uv, const double radius);
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
