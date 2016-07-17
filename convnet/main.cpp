// app to generate examples
// at first, the pipeline into tf can be via tfrecords files

#include "mnist.h"
#include <armadillo>

int main()
{
    std::string filename1a = "../../train-images.idx3-ubyte";
    std::string filename1b = "../../train-labels.idx1-ubyte";
    std::string filename2a = "../../traini.mnist";
    std::string filename2b = "../../trainl.mnist";

    int number_of_images = 60000;
    int image_size = 28 * 28;
    std::vector<arma::mat> vec1;
    arma::colvec vec2 = arma::zeros<arma::colvec>(number_of_images);

    convnet::Mnist mnist;

    mnist.ReadMnistI(filename1a, vec1);
    mnist.ReadMnistL(filename1b, vec2);

    mnist.WriteMnistI(filename2a, vec1);
    mnist.WriteMnistL(filename2b, vec2);

    return 0;
}




