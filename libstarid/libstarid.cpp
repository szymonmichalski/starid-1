#include "libstarid.h"

// default constructor automatically loads a sky object
libstarid::libstarid() {
    std::string skydata = "/home/noah/starid/stars/";
    std::ifstream is1(std::string(skydata + "sky"));
    cereal::BinaryInputArchive iarchive1(is1);
    iarchive1(sky);
}

// load a pairs object
void libstarid::load_pairs() {
    std::string pairsdata = "/home/noah/starid/identification/";
    std::ifstream is2(std::string(pairsdata + "pairs"));
    cereal::BinaryInputArchive iarchive2(is2);
    iarchive2(pairs);
}

Eigen::MatrixXd libstarid::image(int starndx) {
    Eigen::MatrixXd img = starid::pointing_vectors::new_image_matrix(starndx, sky);
    return img;
}

Eigen::MatrixXd libstarid::image_info(int starndx) {
    Eigen::MatrixXd image_info = starid::pointing_vectors::new_image_info(starndx, sky);
    return image_info;
}

Eigen::MatrixXd libstarid::ang_seq_vec(int starndx) {
    Eigen::MatrixXd angseqvec = starid::pointing_vectors::new_ang_seq_vec(starndx, sky);
    return angseqvec;
}

int libstarid::id(starid::image_matrix imgmat) {
    starid::triangles ider(imgmat, pairs);
    int result = ider.id();
    return result;
}
