#include <iostream>
#include <fstream>
#include <string>

#include "skymap_catalog.h"
#include "definitions.h"

int SkymapCatalog::ReadCatalog()
{
    std::ifstream catfile ("../SKYMAP_SKY2000_V5R4.txt");
    if (catfile.is_open()) {

        std::string line;
        while (std::getline(catfile, line)) {

            try {
                float mv1 = std::stof(line.substr(232,5));
                if (mv1 > 8) continue;
                std::cout << mv1 << "\n";
            } catch(...) { }

        }

        catfile.close();

    } else std::cout << "Catalog file not found." << "\n";

    return 0;
}

