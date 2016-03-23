#include "skymap_catalog.h"

#include <iostream>
#include <fstream>
#include <string>

int SkymapCatalog::ReadCatalog()
{
    std::string line;
    std::ifstream catfile ("../SKYMAP_SKY2000_V5R4.txt");
    if (catfile.is_open()) {
        std::getline(catfile,line);
        std::cout << line << "\n";
        catfile.close();
    } else {
        std::cout << "Catalog file not found." << "\n";
    }

    return 0;
}

