/// *libstarid*
///
/// interface cpp eigen and python numpy.
///

#ifndef LIBSTARID_H
#define LIBSTARID_H

#include "sky.h"
#include "pointing_vectors.h"
#include "pairs.h"
#include "triangles.h"

#include "cereal/archives/binary.hpp"
#include <Eigen/Core>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

class libstarid {

public:

    starid::Sky sky;
    starid::Pairs pairs;

    libstarid();


    void load_pairs();

    Eigen::MatrixXd image(int starndx);
    Eigen::MatrixXd yaw_sequence_vector(int starndx);

    int id(starid::image_matrix image);
};

PYBIND11_PLUGIN(libstarid) {
    pybind11::module pymodule("libstarid", "libstarid python module");
    pybind11::class_<libstarid>(pymodule, "libstarid")
        .def(pybind11::init<>())
        .def("image", &libstarid::image, "create star image", pybind11::arg("starndx"))
        .def("load_pairs", &libstarid::load_pairs, "load pairs")
        .def("id", &libstarid::id, "id");
    return pymodule.ptr();
}

#endif
