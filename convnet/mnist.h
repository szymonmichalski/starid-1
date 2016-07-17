#ifndef MNIST_H
#define MNIST_H

#include <armadillo>

namespace convnet {

class Mnist {

public:
    int ReverseInt (int i);

    void ReadMnistI(std::string filename, std::vector<arma::mat> &vec);
    void ReadMnistL(std::string filename, arma::colvec &vec);
    int magic_numberi;
    int magic_numberl;
    int rows;
    int cols;
    int imgcnt;

    void WriteMnistI(std::string filename, std::vector<arma::mat> &vec);
    void WriteMnistL(std::string filename, arma::colvec &vec);

};

}

#endif // MNIST_H
