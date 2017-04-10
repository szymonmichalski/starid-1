#include "sky.h"
#include "star_catalog.h"
#include "globals.h"
#include <cmath>
#include <algorithm>

void stars::Sky::init(std::string fcatin) {
    fcatalog = fcatin;
    t = 0.0;
    Star star;

    data::star_catalog skymapCatalog(fcatalog);
    int starndx = 0;
    for (auto rec : skymapCatalog.star_records) {
        star.starndx = starndx;
        star.skymap_number = rec.skymap_number;
        star.mv = rec.mv1;
        double ra_degrees = 15.0 * (rec.rah + rec.ram/60.0 + rec.ras/3600.0);
        double dec_degrees = rec.decsign * (rec.decd + rec.decm/60.0 + rec.decs/3600.0);
        ra_degrees += (t * rec.pmra_arcsec_per_year) / 3600.0;
        dec_degrees += (t * rec.pmdecsign * rec.pmdec_arcsec_per_year) / 3600.0;
        double ra = ra_degrees * stars::pi / 180.0;
        double dec = dec_degrees * stars::pi / 180.0;
        star.x = std::cos(ra) * std::cos(dec);
        star.y = std::sin(ra) * cos(dec);
        star.z = std::sin(dec);
        xtable.addPair(star.x, starndx);
        ytable.addPair(star.y, starndx);
        ztable.addPair(star.z, starndx);
        stars.push_back(star);
        catalog_lines.push_back(rec.fileLine);
        ++starndx;
    }
    xtable.sort();
    ytable.sort();
    ztable.sort();
}

std::vector<int> stars::Sky::starsNearPoint(double x, double y, double z) {
    double max_ang = 1.4 * stars::image_radius_radians;
    std::vector<int> xring = starsInRing(x, max_ang, xtable);
    std::vector<int> yring = starsInRing(y, max_ang, ytable);
    std::vector<int> zring = starsInRing(z, max_ang, ztable);
    std::vector<int> xy;
    std::set_intersection(xring.begin(), xring.end(), yring.begin(), yring.end(), std::back_inserter(xy));
    std::vector<int> xyz;
    std::set_intersection(xy.begin(), xy.end(), zring.begin(), zring.end(), std::back_inserter(xyz));
    std::vector<int> ndxs;
    for (uint i = 0; i < xyz.size(); ++i) {
        ndxs.push_back(xyz[i]);
    }
    return ndxs;
}

std::vector<int> stars::Sky::starsInRing(double p, double radius, util::FloatIntTable& table)
{
    double pmin, pmax;
    if (p >= cos(radius)) {
        pmin = p*cos(radius) - sqrt(1-(p*p))*sin(radius);
        pmax = 1.0;
    } else if (p <= -cos(radius)) {
        pmin = -1.0;
        pmax = p*cos(radius) + sqrt(1-(p*p))*sin(radius);
    } else {
        pmin = p*cos(radius) - sqrt(1-(p*p))*sin(radius);
        pmax = p*cos(radius) + sqrt(1-(p*p))*sin(radius);
    }
    return table.findInts(pmin, pmax);
}

void stars::Sky::status() {
    std::cout << "number of stars " << stars.size() << "\n";
}

//double UnixTimeToJ2000Offset = 946684800.0;
//std::chrono::time_point<std::chrono::system_clock> tcurrent {std::chrono::system_clock::now()};
//double t {(double(std::chrono::system_clock::to_time_t(tcurrent)) - UnixTimeToJ2000Offset) / 31557600.0}; // julian years
