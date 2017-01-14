#ifndef IMAGE_H
#define IMAGE_H

#include "sky.h"
#include <armadillo>
#include <eigen/Core>
#include "mnist.h"

namespace stars {

class Image {
public:

    void readMnistAxjAxiImage(std::string& imgfile, int imgndx);

    void replaceAxjAxiImage(arma::mat& axjAxiImage, stars::Sky& sky, int starndx);

    arma::mat uvecs;

private:

};

}

#endif
