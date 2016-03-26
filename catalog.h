#ifndef CATALOG_H
#define CATALOG_H

#include <string>
#include <chrono>
#include <vector>

class Catalog
{
public:
    int ReadCatalogFile();

private:
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
        double ra_degrees {0.0};
        double dec_degrees {0.0};
        double mv1 {100.0};
    };
    std::vector<Star> stars_;
    double years_from_j2000_ {0.0};
};

#endif
