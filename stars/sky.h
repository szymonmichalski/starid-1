#ifndef STARS_H
#define STARS_H

#include <armadillo>
#include <util/float_int_table.h>
#include <cereal/access.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

namespace stars {

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
    double ra;
    double dec;
    double x;
    double y;
    double z;
    int starndx;
    template <class Archive> void serialize(Archive& ar) {
        ar(iau_identifier, star_name, variablestar_name);
        ar(skymap_number, hd_number, sao_number, dm_number, hr_number, wds_number, ppm_number);
        ar(blended_position);
        ar(mv1, ra_degrees, dec_degrees, ra, dec, x, y, z, starndx);
    }
};

class Sky {

public:

    std::vector<stars::Star> stars;
    std::vector<std::string> catalogLines;

    void init(std::string fcatalog);

    std::vector<int> starsNearPoint(double x, double y, double z);

    void status();

private:

    double t;
    std::string fcatalog;
    util::FloatIntTable xtable;
    util::FloatIntTable ytable;
    util::FloatIntTable ztable;

    std::vector<int> starsInRing(double p, double radius, util::FloatIntTable& table);

    friend class cereal::access;
    template <class Archive> void serialize(Archive& ar) {
        ar(stars, xtable, ytable, ztable);
    }
};

}

#endif

