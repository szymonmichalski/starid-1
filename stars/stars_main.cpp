#include "sensor.h"
#include "mnist.h"
#include <armadillo>

int main() {
    arma::arma_rng::set_seed_random();
    std::string fsky2000  = "/home/noah/dev/starid/data/SKYMAP_SKY2000_V5R4.txt";
    std::string fref10    = "/home/noah/dev/starid/data/SKYMAP_ten_stars.txt";
    double mv             = 6.5;
    double fov            = 4.0 * arma::datum::pi / 180.0;

    if (true) { // text file for star testset 1 (800, 1600, 2400, ... 8000)
        stars::Stars stars;
        stars.init(fsky2000, mv, fov);
        std::ofstream fout(fref10);
        for (int label = 0; label < 10; ++label) {
            int starndx = 800 * (label + 1);
            fout << stars.catalogLines[starndx];
        }
        fout.close();
    }

    if (false) { // generate star images in mnist format
        bool yaw              = true;
        int number_of_images  = 10000;
        std::string fimg1    = "/home/noah/dev/starid/data/mnist_format/mnist_imagesb.mnist";
        std::string flab1    = "/home/noah/dev/starid/data/mnist_format/mnist_labelsb.mnist";
        std::string fimg2    = "/home/noah/dev/starid/data/mnist_format/starid_imagesb.mnist";
        std::string flab2    = "/home/noah/dev/starid/data/mnist_format/starid_labelsb.mnist";
        stars::Mnist mnist;
        std::vector<arma::mat> images;
        arma::colvec labels = arma::zeros<arma::colvec>(number_of_images);
        mnist.ReadMnistI(fimg1, images);
        mnist.ReadMnistL(flab1, labels);
        stars::Sensor sensor(fsky2000, mv, fov);
        for (int tenscnt = 0; tenscnt < number_of_images/10; ++tenscnt) {
            for (int label = 0; label < 10; ++label) {
                int starndx = 800 * (label + 1);
                arma::mat img = sensor.makeStarImage(starndx);
                labels(10*tenscnt + label) = (double)label;
                images[10*tenscnt + label] = img;
                sensor.status();
            }
        }
        mnist.WriteMnistI(fimg2, images, yaw);
        mnist.WriteMnistL(flab2, labels);
    }

    return 0;
}

