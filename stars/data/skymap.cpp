#include "skymap.h"
#include "globals.h"

data::SkymapCatalog::SkymapCatalog(std::string fcat) {
    std::ifstream catfile (fcat);
    if (catfile.is_open()) {
        std::string line;
        SkymapRecord skyrec;
        while (std::getline(catfile, line)) {
            try {
                try {skyrec.mv1 = std::stof(line.substr(232,6));} catch(...){}
                if (skyrec.mv1 > stars::imageFaintnessLimit) {
                    ++dimStars;
                    continue;
                }
                skyrec.iau_identifier = line.substr(0,27);
                try {skyrec.star_name = line.substr(98,10);} catch(...){}
                try {skyrec.variablestar_name = line.substr(108,10);} catch(...){}
                skyrec.skymap_number = std::stoi(line.substr(27,8));
                try {skyrec.hd_number = std::stoi(line.substr(35,8));} catch(...){}
                try {skyrec.sao_number = std::stoi(line.substr(43,7));} catch(...){}
                try {skyrec.dm_number = std::stoi(line.substr(50,13));} catch(...){}
                try {skyrec.hr_number = std::stoi(line.substr(63,4));} catch(...){}
                try {skyrec.wds_number = std::stoi(line.substr(67,6));} catch(...){}
                try {skyrec.ppm_number = std::stoi(line.substr(83,7));} catch(...){}
                try {skyrec.blended_position = std::stoi(line.substr(146,1));} catch(...){}
                skyrec.rah = std::stof(line.substr(118,2));
                skyrec.ram = std::stof(line.substr(120,2));
                skyrec.ras = std::stof(line.substr(122,7));
                skyrec.decd = std::stof(line.substr(130,2));
                skyrec.decm = std::stof(line.substr(132,2));
                skyrec.decs = std::stof(line.substr(134,6));
                skyrec.pmra_arcsec_per_year = 15.0 * std::stof(line.substr(149,8));
                skyrec.pmdec_arcsec_per_year = std::stof(line.substr(158,7));
                if (line.substr(129,1) == "-")
                    skyrec.decsign = -1.0;
                if (line.substr(157,1) == "-")
                    skyrec.pmdecsign = -1.0;
                skyrec.fileLine = line;
                skymapRecords.push_back(skyrec);
            } catch (...) {
            }
        }
        catfile.close();
    }
}
