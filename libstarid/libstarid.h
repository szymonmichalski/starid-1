/// *libstarid*
///
/// interface cpp eigen and python numpy.
///

#ifndef LIBSTARID_H
#define LIBSTARID_H
#include <cereal/archives/binary.hpp>
#include <Eigen/Core>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include "globals.h"
#include "sky.h"
#include "triangles.h"

class libstarid {

public:

    starid::sky sky;
    starid::pairs pairs;

    // default constructor automatically loads a sky object
    libstarid();
    // load a pairs object
    void load_pairs();

    // 28 by 28 image as a matrix
    Eigen::MatrixXd image(int starndx);
    // image info, pixels and starndxs, as a matrix
    Eigen::MatrixXd image_info(int starndx);
    // sequence of angular observations as a vector
    Eigen::MatrixXd ang_seq_vec(int starndx);

    // identifies the star at the center of the image from triangular structures
    int id(starid::image_matrix image);
};

PYBIND11_PLUGIN(libstarid) {
    pybind11::module pymodule("Libstarid", "libstarid python module");
    pybind11::class_<libstarid>(pymodule, "Libstarid")
        .def(pybind11::init<>())
        .def("image", &libstarid::image, "create star image", pybind11::arg("starndx"))
        .def("image_info", &libstarid::image_info, "create star image info", pybind11::arg("starndx"))
        .def("ang_seq_vec", &libstarid::ang_seq_vec, "create angle sequence vector", pybind11::arg("starndx"))
        .def("load_pairs", &libstarid::load_pairs, "load pairs")
        .def("id", &libstarid::id, "id");
    return pymodule.ptr();
}

#endif
