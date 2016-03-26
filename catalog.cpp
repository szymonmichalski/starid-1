#include <iostream>
#include <fstream>
#include <assert.h>

#include "catalog.h"
#include "definitions.h"

int Catalog::ReadCatalogFile()
{
    std::chrono::time_point<std::chrono::system_clock> current_time {std::chrono::system_clock::now()};
    std::time_t catalog_time {std::chrono::system_clock::to_time_t(current_time)};
    years_from_j2000_ = (catalog_time - double(kUnixTimeToJ2000Offset)) / 31557600.0; // julian years

    std::ifstream catfile ("../SKYMAP_SKY2000_V5R4.txt");
    int good_lines {0};
    int bad_lines {0};
    if (catfile.is_open()) {
        std::string line;
        while (std::getline(catfile, line)) {
            try {
                Star star;
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
                try {star.mv1 = std::stof(line.substr(232,6));} catch(...){}
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
                if (line.substr(129,1).compare("-")) star.dec_degrees = -1.0 * star.dec_degrees;
                star.ra_degrees += (years_from_j2000_ * pmra_arcsec_per_year) / 3600.0;
                star.dec_degrees += (years_from_j2000_ * pmdec_arcsec_per_year) / 3600.0;
                assert(star.ra_degrees >= 0.0 && star.ra_degrees <= 360.0);
                assert(star.dec_degrees >= -90.0 && star.dec_degrees <= 90.0);

                stars_.push_back(star);
                ++good_lines;
//                std::cout << star.iau_identifier << ", " << star.skymap_number << ", " << star.mv1 << "\n";
            } catch (...) {
                ++bad_lines;
            }
        }
        catfile.close();
        std::cout << "good lines " << good_lines << " bad lines " << bad_lines << "\n";
    }
    else std::cout << "catalog file not found" << "\n";
    return 0;
}

