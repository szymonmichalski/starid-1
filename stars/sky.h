/// *sky*
///
/// sky representation as pointing vectors, with methods to get the stars near an arbitrary point.
///

#ifndef STARS_H
#define STARS_H

#include <float_int_table.h>
#include <cereal/access.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

namespace starid {

struct Star {
    int starndx;
    int skymap_number;
    double mv;
    double x;
    double y;
    double z;
    template <class Archive> void serialize(Archive& ar) {
        ar(starndx, skymap_number, mv, x, y, z);
    }
};

class Sky {

public:

    std::vector<starid::Star> stars;
    std::vector<std::string> catalog_lines;

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

