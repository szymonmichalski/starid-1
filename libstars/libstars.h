/// *libstars*
///
/// interface numpy and cpp.
///

#ifndef LIBSTARS_H
#define LIBSTARS_H

#include "sky.h"
#include "pointing_vectors.h"
#include "cereal/archives/binary.hpp"

class libstars {

public:

    stars::Sky sky;

    libstars();

};

#endif
