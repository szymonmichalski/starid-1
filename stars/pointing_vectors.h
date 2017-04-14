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

class pointing_vectors {

public:

    Eigen::MatrixXd pvecs;

    /// *get image vectors* get pointing vector representation of an image
    ///
    void get_pvecs(std::string& imgfile, int imgndx);

//    void axjAxiImageUpdate(arma::mat& axjAxiImage, stars::Sky& sky, int starndx);

private:

    Eigen::Matrix3d rotation_matrix(Eigen::Vector3d& pointing);
    static int reverseInt (int i);
    static Eigen::Matrix<double, 28, 28> read_images_container(std::string& imgfile, int imgndx);
    // void read_labels_container(std::string filename, arma::colvec &labels);
    // void write_images_container(std::string filename, std::vector<arma::mat> &images);
    // void write_labels_contrainer(std::string filename, arma::colvec &labels);

};

}

#endif
