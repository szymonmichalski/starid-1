#include "pointing.h"
#include "catalog.h"
#include "sensor.h"
#include "mnist.h"
#include <armadillo>

int main()
{
    arma::arma_rng::set_seed_random();

    int number_of_images = 60000;

    std::string fm_initi  = "../../mnist_initial_images.mnist";
    std::string fm_initl  = "../../mnist_initial_labels.mnist";

    std::string fm_unyawedi  = "../../mnist_unyawed_images.mnist";
    std::string fm_unyawedl  = "../../mnist_unyawed_labels.mnist";
    std::string fm_yawedi  = "../../mnist_yawed_images.mnist";
    std::string fm_yawedl  = "../../mnist_yawed_labels.mnist";

    std::string fs_unyawedi = "../../starid_unyawed_images.mnist";
    std::string fs_unyawedl = "../../starid_unyawed_labels.mnist";
    std::string fs_yawedi = "../../starid_yawed_images.mnist";
    std::string fs_yawedl = "../../starid_yawed_labels.mnist";

    std::vector<arma::mat> images;
    arma::colvec labels = arma::zeros<arma::colvec>(number_of_images);

    stars::Mnist mnist;

    mnist.ReadMnistI(fm_initi, images);
    mnist.ReadMnistL(fm_initl, labels);

    mnist.WriteMnistI(images, true, fm_yawedi);
    mnist.WriteMnistL(labels, fm_yawedl);

    std::string fcatalog = "../../SKYMAP_SKY2000_V5R4.txt";
    double t = 0.0;
    double mv = 6.5;
    stars::Catalog catalog(fcatalog, t, mv);
    catalog.Status();

    double fov = 4.0 * arma::datum::pi / 180.0;
    stars::Sensor sensor(fov, mv);

    double ra = 0.0 * arma::datum::pi / 180.0;
    double dec = 60.0 * arma::datum::pi / 180.0;
    double yaw = 0.0 * arma::datum::pi / 180.0;
    stars::Pointing pointing(ra, dec, yaw);

    sensor.Click(catalog, pointing);

    return 0;
}

