/// *libstars*
///
/// interface numpy and eigen.
///

#ifndef LIBSTARS_H
#define LIBSTARS_H

#include "sky.h"
#include "pointing_vectors.h"
#include "cereal/archives/binary.hpp"
#include <Eigen/Core>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

class libstars {

public:

    stars::Sky sky;

    libstars();

    Eigen::MatrixXd image(int starndx);

};

PYBIND11_PLUGIN(libstars) {
    pybind11::module pymodule("libstars", "libstars python module");
    pybind11::class_<libstars>(pymodule, "libstars")
        .def(pybind11::init<>())
        .def("image", &libstars::image);
    return pymodule.ptr();
}

#endif
