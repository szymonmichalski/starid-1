/// *pointing vectors*
///
/// star representations as pointing vectors and binary images container on disk
///
#ifndef IMAGE_H
#define IMAGE_H

#include "sky.h"
#include <eigen/Core>
#include <fstream>

namespace stars {

using image_matrix = Eigen::Matrix<double, 28, 28>;

class pointing_vectors {

public:

    /// *new image matrix* create an axi axj image matrix for the star, with a random yaw
    ///
    static image_matrix new_image_matrix(int starndx, stars::Sky &sky);
    static image_matrix read_image_matrix(std::string &imgfile, int imgndx);

    /// *get pointing vectors* get pointing vector representation of an image
    ///
    static Eigen::MatrixXd get_pvecs_from_imgmat(image_matrix &imgmat);


private:

    static Eigen::Matrix3d rotation_matrix(Eigen::Vector3d &pointing);
    static int reverseInt (int i);
    static Eigen::Vector3d crossprod(Eigen::Vector3d &u, Eigen::Vector3d &v);

    // following still need to switched from armadillo to eigen
    // void read_labels_container(std::string filename, arma::colvec &labels);
    // void write_images_container(std::string filename, std::vector<arma::mat> &images);
    // void write_labels_contrainer(std::string filename, arma::colvec &labels);

};

}

#endif
