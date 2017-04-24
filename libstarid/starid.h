/// *libstarid*
///
/// interface numpy and cpp.
///

#ifndef STARID_H
#define STARID_H

#include "sky.h"
#include "pointing_vectors.h"
#include "cereal/archives/binary.hpp"

class starid {

public:

    stars::Sky sky;

    starid();

};

#endif
