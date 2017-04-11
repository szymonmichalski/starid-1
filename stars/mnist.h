#ifndef MNIST_H
#define MNIST_H

#include <eigen/Core>

namespace data {

class Mnist {

public:

    static Eigen::Matrix<double, 28, 28> readImage(std::string& imgfile, int imgndx);

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
