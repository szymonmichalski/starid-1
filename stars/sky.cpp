#include "sky.h"
#include "skymap.h"
#include <cassert>

void stars::Sky::init(std::string fcatin, double mvin) {
    arma::arma_rng::set_seed_random();
    fcatalog = fcatin;
    mv = mvin;
    t = 0.0;
    Star star;

    data::SkymapCatalog skymapCatalog(fcatalog, mv);
    int starndx {0};
    for (auto r : skymapCatalog.skymapRecords) {
        star.starndx = starndx;
        star.iau_identifier = r.iau_identifier;
        star.star_name = r.star_name;
        star.variablestar_name = r.variablestar_name;
        star.skymap_number = r.skymap_number;
        star.hd_number = r.hd_number;
        star.sao_number = r.sao_number;
        star.dm_number = r.dm_number;
        star.hr_number = r.hr_number;
        star.wds_number = r.wds_number;
        star.ppm_number = r.ppm_number;
        star.blended_position = r.blended_position;

        star.ra_degrees = 15.0 * (r.rah + r.ram/60.0 + r.ras/3600.0);
        star.dec_degrees = r.decsign * (r.decd + r.decm/60.0 + r.decs/3600.0);
        star.ra_degrees += (t * r.pmra_arcsec_per_year) / 3600.0;
        star.dec_degrees += (t * r.pmdecsign * r.pmdec_arcsec_per_year) / 3600.0;
        assert (star.ra_degrees >= 0.0 && star.ra_degrees <= 360.0);
        assert (star.dec_degrees >= -90.0 && star.dec_degrees <= 90.0);

        double ra = star.ra_degrees * arma::datum::pi / 180.0;
        double dec = star.dec_degrees * arma::datum::pi / 180.0;
        star.ra = ra;
        star.dec = dec;
        star.x = cos(ra)*cos(dec);
        star.y = sin(ra)*cos(dec);
        star.z = sin(dec);

        xtable.addPair(star.x, starndx);
        ytable.addPair(star.y, starndx);
        ztable.addPair(star.z, starndx);
        stars.push_back(star);
        catalogLines.push_back(r.fileLine);
        ++starndx;
    }
    xtable.sort();
    ytable.sort();
    ztable.sort();
}

std::vector<int> stars::Sky::starsNearPoint(double x, double y, double z, double radius) {
    std::vector<int> xring = starsInRing(x, radius, xtable);
    std::vector<int> yring = starsInRing(y, radius, ytable);
    std::vector<int> zring = starsInRing(z, radius, ztable);
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
    assert (pmin >= -1.0 && pmax <= 1.0);
    return table.findInts(pmin, pmax);
}

void stars::Sky::status() {
    std::cout << "number of stars " << stars.size() << "\n";
}

//double UnixTimeToJ2000Offset = 946684800.0;
//std::chrono::time_point<std::chrono::system_clock> tcurrent {std::chrono::system_clock::now()};
//double t {(double(std::chrono::system_clock::to_time_t(tcurrent)) - UnixTimeToJ2000Offset) / 31557600.0}; // julian years
