// app to generate examples
// at first, the pipeline into tf can be via tfrecords files

#include "mnist.h"
#include <armadillo>

int main() {
    using namespace std;
    int number_of_images = 60000;
    string f_mnist0a  = "../../mnist_initial_images.mnist";
    string f_mnist0b  = "../../mnist_initial_labels.mnist";

    string f_mnist1a  = "../../mnist_unyawed_images.mnist";
    string f_mnist1b  = "../../mnist_unyawed_labels.mnist";
    string f_starid1a = "../../starid_unyawed_images.mnist";
    string f_starid1b = "../../starid_unyawed_labels.mnist";

    string f_mnist2a  = "../../mnist_yawed_images.mnist";
    string f_mnist2b  = "../../minst_yawed_labels.mnist";
    string f_starid2a = "../../starid_yawed_images.mnist";
    string f_starid2b = "../../starid_yawed_labels.mnist";

    std::vector<arma::mat> vec1;
    arma::colvec vec2 = arma::zeros<arma::colvec>(number_of_images);

    convnet::Mnist mnist;

    mnist.ReadMnistI(f_mnist0a, vec1);
    mnist.WriteMnistI(f_mnist1a, vec1);

    mnist.ReadMnistL(f_mnist0b, vec2);
    mnist.WriteMnistL(f_mnist1b, vec2);

    return 0;
}




