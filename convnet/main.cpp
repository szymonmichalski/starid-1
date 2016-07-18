// app to generate examples
// at first, the pipeline into tf can be via tfrecords files

#include "mnist.h"
#include <armadillo>

int main()
{
    using namespace std;

    string f_mnist1a  = "../../mnist_unyawed_images.mnist";
    string f_mnist1b  = "../../mnist_unyawed_labels.mnist";

    string f_mnist2a  = "../../mnist_yawed_images.mnist";
    string f_mnist2b  = "../../minst_yawed_labels.mnist";

    string f_starid1a = "../../starid_unyawed_images.mnist";
    string f_starid1b = "../../starid_unyawed_labels.mnist";

    string f_starid2a = "../../starid_yawed_images.mnist";
    string f_starid2b = "../../starid_yawed_labels.mnist";

    int number_of_images = 60000;
    int image_size = 28 * 28;
    std::vector<arma::mat> vec1;
    arma::colvec vec2 = arma::zeros<arma::colvec>(number_of_images);

    convnet::Mnist mnist;

    mnist.ReadMnistI(fname0a, vec1);
    mnist.ReadMnistL(fname02, vec2);

    mnist.WriteMnistI(fname1a1, vec1);
    mnist.WriteMnistL(fname1a2, vec2);

    return 0;
}




