#include "sensor.h"
#include "mnist.h"
#include <armadillo>

int main() {
    bool mnist_to_starid = true;
    bool yaw = false;
    int number_of_images = 60000;
    std::string f_img1  = "../../mnist_initial_images.mnist";
    std::string f_lab1  = "../../mnist_initial_labels.mnist";
    std::string f_img2  = "../../starid_unyawed_images.mnist";
    std::string f_lab2  = "../../starid_unyawed_labels.mnist";

    stars::Mnist mnist;
    std::vector<arma::mat> images;
    arma::colvec labels = arma::zeros<arma::colvec>(number_of_images);
    mnist.ReadMnistI(f_img1, images);
    mnist.ReadMnistL(f_lab1, labels);

    if (mnist_to_starid) {
        stars::Sensor sensor;
        for (uint itrcnt = 0; itrcnt < 6000; ++itrcnt) {
            for (uint label = 0; label < 10; ++label) {
                uint starndx = 800 * (label + 1);
                arma::mat img = sensor.Image(starndx);
                labels(10*itrcnt + label) = (double)label;
                images[10*itrcnt + label] = img;
                sensor.Status();
                int a = 1;
            }
        }
    }

    mnist.WriteMnistI(f_img2, images, yaw);
    mnist.WriteMnistL(f_lab2, labels);

    return 0;
}

