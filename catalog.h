#ifndef CATALOG_H
#define CATALOG_H

#include <string>
#include <vector>

#include "def.h"

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
    double ra {0.0}; // radians
    double dec {0.0}; //radians
    double x {0.0};
    double y {0.0};
    double z {0.0};
};

class Catalog
{
public:
    Catalog(const std::string& catalog_file, double years_from_j2000=0.0, double max_mv=7.2);

private:
    std::vector<Star> stars_;

};

#endif
