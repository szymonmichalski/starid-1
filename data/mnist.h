#ifndef MNIST_H
#define MNIST_H

#include <armadillo>

namespace data {

class Mnist {

public:

    void ReadMnistI(std::string filename, std::vector<arma::mat> &vec);
    void ReadMnistL(std::string filename, arma::colvec &vec);

    void WriteMnistI(std::string filename, std::vector<arma::mat> &vec, bool yaw);
    void WriteMnistL(std::string filename, arma::colvec &vec);

private:

    int magic_numberi;
    int magic_numberl;
    int rows;
    int cols;
    int imgcnt;
    int ReverseInt (int i);
    void Yaw(arma::mat &img, double angle);

};

}

#endif // MNIST_H
