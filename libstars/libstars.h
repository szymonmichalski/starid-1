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

class starsclass {

public:

    stars::Sky sky;

    starsclass();

    Eigen::Matrix2d add(Eigen::Matrix2d in) {
        Eigen::Matrix2d out = in;
        return out;
    }

};

PYBIND11_PLUGIN(libstars) {
    pybind11::module pymodule("libstars", "description string");
    pybind11::class_<starsclass>(pymodule, "starsclass")
        .def(pybind11::init<>())
        .def("add", &starsclass::add);
    return pymodule.ptr();
}

#endif
