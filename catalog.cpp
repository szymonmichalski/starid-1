#include "catalog.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <algorithm>

catalog::Catalog::Catalog(const std::string& catalog_file, double years_from_j2000, double max_mv)
{
    std::ifstream catfile (catalog_file);
    int good_stars {0};
    int dim_stars {0};
    int error_stars {0};
    if (catfile.is_open()) {
        std::string line;
        while (std::getline(catfile, line)) {
            try {
                Star star;
                try {star.mv1 = std::stof(line.substr(232,6));} catch(...){}
                if (star.mv1 > max_mv) {
                    ++dim_stars;
                    continue;
                }

                star.iau_identifier = line.substr(0,27);
                try {star.star_name = line.substr(98,10);} catch(...){}
                try {star.variablestar_name = line.substr(108,10);} catch(...){}
                star.skymap_number = std::stoi(line.substr(27,8));
                try {star.hd_number = std::stoi(line.substr(35,8));} catch(...){}
                try {star.sao_number = std::stoi(line.substr(43,7));} catch(...){}
                try {star.dm_number = std::stoi(line.substr(50,13));} catch(...){}
                try {star.hr_number = std::stoi(line.substr(63,4));} catch(...){}
                try {star.wds_number = std::stoi(line.substr(67,6));} catch(...){}
                try {star.ppm_number = std::stoi(line.substr(83,7));} catch(...){}
                try {star.blended_position = std::stoi(line.substr(146,1));} catch(...){}
                double rah = std::stof(line.substr(118,2));
                double ram = std::stof(line.substr(120,2));
                double ras = std::stof(line.substr(122,7));
                double decd = std::stof(line.substr(130,2));
                double decm = std::stof(line.substr(132,2));
                double decs = std::stof(line.substr(134,6));
                double pmra_arcsec_per_year = 15.0 * std::stof(line.substr(149,8));
                double pmdec_arcsec_per_year = std::stof(line.substr(158,7));
                if (line.substr(157,1).compare("-")) pmdec_arcsec_per_year = -1.0 * pmdec_arcsec_per_year;

                star.ra_degrees = 15.0 * (rah + ram/60.0 + ras/3600.0);
                star.dec_degrees = decd + decm/60.0 + decs/3600.0;
                if (line.substr(129,1).compare("+")) star.dec_degrees = -1.0 * star.dec_degrees;
                star.ra_degrees += (years_from_j2000 * pmra_arcsec_per_year) / 3600.0;
                star.dec_degrees += (years_from_j2000 * pmdec_arcsec_per_year) / 3600.0;
                assert (star.ra_degrees >= 0.0 && star.ra_degrees <= 360.0);
                assert (star.dec_degrees >= -90.0 && star.dec_degrees <= 90.0);
                star.ra = star.ra_degrees*util::pi/180.0;
                star.dec = star.dec_degrees*util::pi/180.0;
                util::UnitVector unit_vector(star.ra, star.dec);
                star.x = unit_vector.x;
                star.y = unit_vector.y;
                star.z = unit_vector.z;

                stars_.push_back(star);
                ++good_stars;
            } catch (...) {
                ++error_stars;
            }
        }
        catfile.close();
        std::cout << "good stars " << good_stars << " dim stars " << dim_stars << " error_stars " << error_stars << "\n";
    } else {
        std::cout << "catalog file not found" << "\n";
    }

    int ndx = 0;
    for (catalog::Star star : stars_) {
        std::pair<double,int> xpair;
        xpair.first = star.x;
        xpair.second = ndx;
        xpairs_.push_back(xpair);
        std::pair<double,int> ypair;
        ypair.first = star.y;
        ypair.second = ndx;
        ypairs_.push_back(ypair);
        std::pair<double,int> zpair;
        zpair.first = star.z;
        zpair.second = ndx;
        zpairs_.push_back(zpair);
        ++ndx;
    }
    xfinder_.sortDoubles(xpairs_);
    yfinder_.sortDoubles(ypairs_);
    zfinder_.sortDoubles(zpairs_);
}

std::vector<int> catalog::Catalog::StarsNearPoint(const double ra, const double dec, const double radius) {
    util::UnitVector unit_vector(ra, dec);

    double xmin, xmax;
    double x {unit_vector.x};
    if (x >= cos(radius)) {
        xmin = x*cos(radius) - sqrt(1-(x*x))*sin(radius);
        xmax = 1.0;
    } else if (x <= -cos(radius)) {
        xmin = -1.0;
        xmax = x*cos(radius) + sqrt(1-(x*x))*sin(radius);
    } else {
        xmin = x*cos(radius) - sqrt(1-(x*x))*sin(radius);
        xmax = x*cos(radius) + sqrt(1-(x*x))*sin(radius);
    }
    assert (xmin >= -1.0 && xmax <= 1.0);
    std::vector<int> xring = xfinder_.findIndexes(xmin, xmax);
    std::sort(xring.begin(),xring.end());

    double ymin, ymax;
    double y {unit_vector.y};
    if (y >= cos(radius)) {
        ymin = y*cos(radius) - sqrt(1-(y*y))*sin(radius);
        ymax = 1.0;
    } else if (y <= -cos(radius)) {
        ymin = -1.0;
        ymax = y*cos(radius) + sqrt(1-(y*y))*sin(radius);
    } else {
        ymin = y*cos(radius) - sqrt(1-(y*y))*sin(radius);
        ymax = y*cos(radius) + sqrt(1-(y*y))*sin(radius);
    }
    assert (ymin >= -1.0 && ymax <= 1.0);
    std::vector<int> yring = yfinder_.findIndexes(ymin, ymax);
    std::sort(yring.begin(),yring.end());

    double zmin, zmax;
    double z {unit_vector.z};
    if (z >= cos(radius)) {
        zmin = z*cos(radius) - sqrt(1-(z*z))*sin(radius);
        zmax = 1.0;
    } else if (z <= -cos(radius)) {
        zmin = -1.0;
        zmax = z*cos(radius) + sqrt(1-(z*z))*sin(radius);
    } else {
        zmin = z*cos(radius) - sqrt(1-(z*z))*sin(radius);
        zmax = z*cos(radius) + sqrt(1-(z*z))*sin(radius);
    }
    assert (zmin >= -1.0 && zmax <= 1.0);
    std::vector<int> zring = zfinder_.findIndexes(zmin, zmax);
    std::sort(zring.begin(),zring.end());

    std::vector<int> xy;
    std::set_intersection(xring.begin(),xring.end(),yring.begin(),yring.end(),
                          std::back_inserter(xy));
    std::vector<int> xyz;
    std::set_intersection(xy.begin(),xy.end(),zring.begin(),zring.end(),
                          std::back_inserter(xyz));

    return xyz;
}

void catalog::Catalog::printStar(int ndx) {
    std::cout << ndx << " " << stars_[ndx].star_name << "\n";
}
