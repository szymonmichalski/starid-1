#include "libstars.h"

libstars::libstars() {
    std::string datadir = "/home/noah/starid/stars/data/";
    std::ifstream is1(std::string(datadir + "sky"));
    cereal::BinaryInputArchive iarchive1(is1);
    iarchive1(sky);
}

Eigen::MatrixXd libstars::image(int starndx) {
    Eigen::MatrixXd img = stars::pointing_vectors::new_image_matrix(starndx, sky);;
    return img;
}
