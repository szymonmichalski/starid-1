#include "image.h"
#include <cmath>
#include "globals.h"

std::random_device r;
std::default_random_engine e1(r());
std::uniform_real_distribution<double> unitscatter(0, 1);

void stars::Image::axjAxiImageReadMnist(std::string& imgfile, int imgndx) {
    Eigen::Matrix<double, 28, 28> axjAxiImage = data::Mnist::readImage(imgfile, imgndx);
    // center star uvec is implicit in the image
    // get other star uvecs from image data
    uvecs.zeros(100,3);
    int uvecsndx = 0;
    for (int axjndx = 0; axjndx < 28; ++axjndx) {
        for (int axindx = 0; axindx < 28; ++axindx) {
            if (axjAxiImage(axjndx, axindx) > 0) { // there's a star inside axjndx, axindx
                double x = (-14.0 + (double)axindx + unitscatter(e1)) * stars::imagePixelUnitVectors;
                double y = (+14.0 - (double)axjndx - unitscatter(e1)) * stars::imagePixelUnitVectors;
                uvecs(uvecsndx,0) = x;
                uvecs(uvecsndx,1) = y;
                uvecs(uvecsndx,2) = std::sqrt(1 - x*x - y*y);
                ++uvecsndx;
            }
        }
    }
    uvecs.shed_rows(uvecsndx, 99);
}

void stars::Image::axjAxiImageUpdate(arma::mat& axjAxiImage, stars::Sky& sky, int starndx) {
    arma::vec pointing(3); // pointing vec to image center star
    pointing(0) = sky.stars[starndx].x;
    pointing(1) = sky.stars[starndx].y;
    pointing(2) = sky.stars[starndx].z;
    // get icrf uvecs of other stars
    std::vector<int> starndxs = sky.starsNearPoint(pointing(0), pointing(1), pointing(2));
    uvecs.zeros(100,3);
    int uvecsndx = 0;
    for (auto ndx : starndxs) {
        uvecs(uvecsndx,0) = sky.stars[ndx].x;
        uvecs(uvecsndx,1) = sky.stars[ndx].y;
        uvecs(uvecsndx,2) = sky.stars[ndx].z;
        ++uvecsndx;
    }
    uvecs.shed_rows(uvecsndx, 99);
    // rotate uvecs from icrf to image frame
    double yaw = unitscatter(e1) * 2 * M_PI;
    arma::mat attitude = rotationMatrix(pointing, yaw);
    uvecs = arma::trans( arma::trans(attitude) * arma::trans(uvecs) );
    // update axjaxiimage
    axjAxiImage.zeros();
    for (int ndx = 0; ndx < uvecsndx; ++ndx) {
        double x = uvecs(ndx,0);
        double y = uvecs(ndx,1);
        int axjndx = 0; //todo
        int axindx = 0;
        axjAxiImage(axjndx, axindx) = 255.0;
    }
}

arma::mat stars::Image::rotationMatrix(arma::vec& pointing, double yaw) {
    arma::mat rm;
    rm.eye(3,3);
    arma::vec bz = pointing;
    arma::vec iz = { 0.0, 0.0, 1.0 };
    arma::vec b1x = arma::cross(bz,iz);
    b1x = arma::normalise(b1x);
    arma::vec b1y = arma::cross(bz,b1x);
    b1y = arma::normalise(b1y);
    arma::vec bx = std::cos(yaw) * b1x + std::sin(yaw) * b1y;
    arma::vec by = std::sin(yaw) * b1x + std::cos(yaw) * b1y;
    rm.col(0) = arma::normalise(bx);
    rm.col(1) = arma::normalise(by);
    rm.col(2) = bz;
    return rm;
}
