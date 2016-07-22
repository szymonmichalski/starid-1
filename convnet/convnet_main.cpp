// app to generate examples
// at first, the pipeline into tf can be via tfrecords files

#include "mnist.h"
#include <armadillo>

int main() {
    arma::arma_rng::set_seed_random();

    int number_of_images = 60000;

    std::string fm_initi  = "../../mnist_initial_images.mnist";
    std::string fm_initl  = "../../mnist_initial_labels.mnist";

    std::string fm_unyawedi  = "../../mnist_unyawed_images.mnist";
    std::string fm_unyawedl  = "../../mnist_unyawed_labels.mnist";
    std::string fm_yawedi  = "../../mnist_yawed_images.mnist";
    std::string fm_yawedl  = "../../minst_yawed_labels.mnist";

    std::string fs_unyawedi = "../../starid_unyawed_images.mnist";
    std::string fs_unyawedl = "../../starid_unyawed_labels.mnist";
    std::string fs_yawedi = "../../starid_yawed_images.mnist";
    std::string fs_yawedl = "../../starid_yawed_labels.mnist";

    std::vector<arma::mat> images;
    arma::colvec labels = arma::zeros<arma::colvec>(number_of_images);

    convnet::Mnist mnist;

    mnist.ReadMnistI(fm_initi, images);
    mnist.ReadMnistL(fm_initl, labels);

    mnist.WriteMnistI(images, true, fm_yawedi);
    mnist.WriteMnistL(labels, fm_yawedl);

    return 0;
}




