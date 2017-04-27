/// *libstars*
///
/// interface numpy and eigen.
///

#ifndef LIBSTARS_H
#define LIBSTARS_H

#include "sky.h"
#include "pointing_vectors.h"
#include "pairs.h"
#include "star_identifier.h"

#include "cereal/archives/binary.hpp"
#include <Eigen/Core>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

class libstars {

public:

    stars::Sky sky;
    stars::Pairs pairs;

    libstars();
    void load_pairs();
    Eigen::MatrixXd image(int starndx);
    int id(stars::image_matrix image);
};

PYBIND11_PLUGIN(libstars) {
    pybind11::module pymodule("libstars", "libstars python module");
    pybind11::class_<libstars>(pymodule, "libstars")
        .def(pybind11::init<>())
        .def("image", &libstars::image, "create star image", pybind11::arg("starndx"))
        .def("load_pairs", &libstars::load_pairs, "load pairs")
        .def("id", &libstars::id, "id");
    return pymodule.ptr();
}

#endif
