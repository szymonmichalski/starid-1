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

//    if (0) { // generate star images in mnist format
//        int number_of_images  = 60000; // 60k for training file, 10k for test file
//        std::string fimg1    = "/home/noah/dev/starid/data/mnist_format/mnist_imagesb.mnist";
//        std::string flab1    = "/home/noah/dev/starid/data/mnist_format/mnist_labelsb.mnist";
//        std::string fimg2    = "/home/noah/dev/starid/data/mnist_format/starid_imagesb.mnist";
//        std::string flab2    = "/home/noah/dev/starid/data/mnist_format/starid_labelsb.mnist";
//        data::Mnist mnist;
//        std::vector<arma::mat> images;
//        arma::colvec labels = arma::zeros<arma::colvec>(number_of_images);
//        mnist.ReadMnistI(fimg1, images);
//        mnist.ReadMnistL(flab1, labels);
//        stars::Sensor sensor(f10stars, mv, fov);
//        for (int tenscnt = 0; tenscnt < number_of_images/10; ++tenscnt) {
//            for (int label = 0; label < 10; ++label) {
//                int starndx = 800 * (label+1);
//                arma::mat img = sensor.makeStarImage(starndx);
//                labels(10*tenscnt + label) = (double)label;
//                images[10*tenscnt + label] = img;
//                //sensor.status();
//            }
//        }
//        //mnist.WriteMnistI(fimg2, images, yaw);
//        //mnist.WriteMnistL(flab2, labels);
//    }
