#ifndef MNIST_H
#define MNIST_H

#include <armadillo>

namespace convnet {

class Mnist {

public:
    void WriteMnistI(std::string filename, std::vector<arma::mat> &vec);
    void WriteMnistL(std::string filename, arma::colvec &vec);
    void ReadMnistI(std::string filename, std::vector<arma::mat> &vec);
    void ReadMnistL(std::string filename, arma::colvec &vec);

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
