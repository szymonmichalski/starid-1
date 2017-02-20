#ifndef IMAGE_H
#define IMAGE_H

#include "sky.h"
#include <armadillo>
#include <eigen/Core>
#include "util/mnist.h"

namespace stars {

class Image {
public:

    void axjAxiImageReadMnist(std::string& imgfile, int imgndx);

    void axjAxiImageUpdate(arma::mat& axjAxiImage, stars::Sky& sky, int starndx);

    arma::mat rotationMatrix(arma::vec& pointing);

    arma::mat uvecs;

private:

};

}

#endif
