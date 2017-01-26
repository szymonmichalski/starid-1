#ifndef IMAGE_H
#define IMAGE_H

#include "sky.h"
#include <armadillo>
#include <eigen/Core>
#include "mnist.h"

namespace stars {

class Image {
public:

    ///
    /// \brief axjAxiImageReadMnist
    /// \param imgfile
    /// \param imgndx
    ///
    void axjAxiImageReadMnist(std::string& imgfile, int imgndx);

    ///
    /// \brief axjAxiImageUpdate
    /// \param axjAxiImage
    /// \param sky
    /// \param starndx
    ///
    void axjAxiImageUpdate(arma::mat& axjAxiImage, stars::Sky& sky, int starndx);

    arma::mat rotationMatrix(arma::vec& pointing);

    arma::mat uvecs;

private:

};

}

#endif
