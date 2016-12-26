#ifndef SKYMAP_H
#define SKYMAP_H

#include <armadillo>

namespace data {

struct SkymapRecord {
    double mv1;
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
    double rah;
    double ram;
    double ras;
    double decd;
    double decm;
    double decs;
    double pmra_arcsec_per_year;
    double pmdec_arcsec_per_year;
    double decsign;
    double pmdecsign;
    std::string fileLine;
};

class SkymapCatalog {

public:

    SkymapCatalog(std::string fcat, double mv);
    std::vector<data::SkymapRecord> skymapRecords;
    int dimStars;

};

}

#endif // SKYMAP_H
