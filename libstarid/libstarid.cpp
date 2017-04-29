#include "libstarid.h"

libstarid::libstarid() {
    std::string datadir = "/home/noah/starid/stars/data/";
    std::ifstream is1(std::string(datadir + "sky"));
    cereal::BinaryInputArchive iarchive1(is1);
    iarchive1(sky);
}

void libstarid::load_pairs() {
    std::string datadir = "/home/noah/starid/stars/data/";
    std::ifstream is2(std::string(datadir + "pairs"));
    cereal::BinaryInputArchive iarchive2(is2);
    iarchive2(pairs);
}

Eigen::MatrixXd libstarid::image(int starndx) {
    Eigen::MatrixXd img = starid::pointing_vectors::new_image_matrix(starndx, sky);;
    return img;
}

int libstarid::id(starid::image_matrix imgmat) {
    starid::triangles ider(imgmat, pairs);
    int result = ider.id();
    return result;
}
