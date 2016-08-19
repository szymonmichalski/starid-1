#include "sensor.h"
#include "mnist.h"
#include <armadillo>

int main() {
    arma::arma_rng::set_seed_random();

    bool mnist_to_starid  = true;
    bool yaw              = true;
    int number_of_images  = 10000;
    std::string f_img1    = "/home/noah/dev/starid_data/mnist_format/mnist_imagesb.mnist";
    std::string f_lab1    = "/home/noah/dev/starid_data/mnist_format/mnist_labelsb.mnist";
    std::string f_img2    = "/home/noah/dev/starid_data/mnist_format/starid_imagesb.mnist";
    std::string f_lab2    = "/home/noah/dev/starid_data/mnist_format/starid_labelsb.mnist";

    std::string f_catalog = "/home/noah/dev/SKYMAP_SKY2000_V5R4.txt";
    double mv             = 6.5;
    double fov            = 4.0 * arma::datum::pi / 180.0;

    stars::Mnist mnist;
    std::vector<arma::mat> images;
    arma::colvec labels = arma::zeros<arma::colvec>(number_of_images);
    mnist.ReadMnistI(f_img1, images);
    mnist.ReadMnistL(f_lab1, labels);

    if (mnist_to_starid) {

        stars::Sensor sensor(f_catalog, mv, fov);

        for (uint itrcnt = 0; itrcnt < number_of_images/10; ++itrcnt) {

            for (uint label = 0; label < 10; ++label) {
                uint starndx = 800 * (label + 1);
                arma::mat img = sensor.MakeStarImage(starndx);
                labels(10*itrcnt + label) = (double)label;
                images[10*itrcnt + label] = img;
                sensor.Status();
            }

        }

    }

    mnist.WriteMnistI(f_img2, images, yaw);
    mnist.WriteMnistL(f_lab2, labels);

    return 0;
}

