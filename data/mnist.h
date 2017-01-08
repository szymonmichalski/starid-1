#ifndef MNIST_H
#define MNIST_H

#include <armadillo>
#include <eigen/Core>

namespace data {

class Mnist {

public:

    static Eigen::Matrix<double, 28, 28> readImage(int imgndx);

    void readMnistI(std::string filename, std::vector<arma::mat> &vec);
    void readMnistL(std::string filename, arma::colvec &vec);
    void writeMnistI(std::string filename, std::vector<arma::mat> &vec, bool performYaw);
    void writeMnistL(std::string filename, arma::colvec &vec);

private:

    static int reverseInt (int i);

    int magic_numberi;
    int magic_numberl;
    int rows;
    int cols;
    int imgcnt;
    void performYaw(arma::mat &img, double angle);

};

}

#endif
