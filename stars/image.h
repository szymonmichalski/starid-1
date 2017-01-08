#ifndef IMAGE_H
#define IMAGE_H

#include "sky.h"
#include <armadillo>
#include <eigen/Core>
#include "mnist.h"

namespace stars {

class Image {
public:

    void useMnistImage(int imgndx);

    arma::mat uvecs;

private:

};

}

#endif
