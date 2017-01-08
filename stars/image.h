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





//    Sensor(std::string fcatalog, double mv, double fov);

//    void status();

//    arma::mat makeStarImage(uint starndx);

//    arma::mat rotationMatrix(arma::vec& pointing, double yaw = 0);

//    double sgn(double x);

//    arma::vec rm2q(arma::mat& rm);

//    arma::vec quaternion(arma::vec& pointing, double yaw);

//    arma::vec qmult(arma::vec& q1, arma::vec& q2);

//    arma::vec qconj(arma::vec& q);

//    arma::vec rv2q(arma::vec& rv);

//    arma::vec q2rv(arma::vec& q);

//    arma::vec qdif2rv(arma::vec& q1, arma::vec& q2a);

//    arma::mat q2rm(arma::vec& q);
