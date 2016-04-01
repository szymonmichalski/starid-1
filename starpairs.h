#ifndef STARPAIRS_H
#define STARPAIRS_H

#include "util.h"
#include "catalog.h"

namespace starpairs {

class Star {
public:
    Star(int catndx, catalog::Catalog& cat);
private:
    int catndx_;
    util::UnitVector uvec_;
};

class StarPairs {
public:
    StarPairs();
private:
};

}

#endif // STARPAIRS_H
