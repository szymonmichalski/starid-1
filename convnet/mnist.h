#ifndef MNIST_H
#define MNIST_H

#include <armadillo>

namespace convnet {

class Mnist {

public:

    void ReadMnistI(std::string filename, std::vector<arma::mat> &vec);
    void ReadMnistL(std::string filename, arma::colvec &vec);

    void WriteMnistI(std::vector<arma::mat> &vec, bool yaw, std::string filename);
    void WriteMnistL(arma::colvec &vec, std::string filename);

private:

    int magic_numberi;
    int magic_numberl;
    int rows;
    int cols;
    int imgcnt;
    int ReverseInt (int i);

};

}

#endif // MNIST_H
