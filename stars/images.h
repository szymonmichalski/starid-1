/// **images**
///
/// image representations as pointing vectors and binary images container on disk
///
#ifndef IMAGE_H
#define IMAGE_H

#include "sky.h"
#include <eigen/Core>
#include <fstream>

namespace stars {

class Images {

public:

    Eigen::MatrixXd uvecs;

    /// *read images container* get an image from an images container.
    ///
    static Eigen::Matrix<double, 28, 28> read_images_container(std::string& imgfile, int imgndx);

    /// *get image vectors* get pointing vector representation of an image
    void get_image_vectors(std::string& imgfile, int imgndx);

//    void axjAxiImageUpdate(arma::mat& axjAxiImage, stars::Sky& sky, int starndx);

//    arma::mat rotationMatrix(arma::vec& pointing);

//    void readAxjAxiImages(std::string filename, std::vector<arma::mat> &images);

//    void readLabels(std::string filename, arma::colvec &labels);

//    void writeImages(std::string filename, std::vector<arma::mat> &images);

//    void writeLabels(std::string filename, arma::colvec &labels);

private:

    static int reverseInt (int i);

    int magnumimg;
    int magnumlab;
    int imgcnt;

    // axj, axi plane quantized to
    // axjndx, axindx plane
    // (axjndx inverted-y-like row-like), (axindx x-like col-like) plane
    int axjcnt; // 28
    int axicnt; // 28

};

}

#endif
