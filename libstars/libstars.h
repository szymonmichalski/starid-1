/// *libstars*
///
/// interface numpy and cpp.
///

#ifndef LIBSTARS_H
#define LIBSTARS_H

#include "sky.h"
#include "pointing_vectors.h"
#include "cereal/archives/binary.hpp"
#include <pybind11/pybind11.h>

class libstars {

public:

    stars::Sky sky;

    libstars();

};

namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

PYBIND11_PLUGIN(libstars) {
    py::module m("libstars", "test");

    m.def("add", &add, "A function which adds two numbers");

    return m.ptr();
}

#endif
