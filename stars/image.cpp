#include "image.h"
#include <cmath>
#include "globals.h"

void stars::Image::readMnistAxjAxiImage(std::string& imgfile, int imgndx) {
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_real_distribution<double> unitscatter(0, 1);
    Eigen::Matrix<double, 28, 28> image = data::Mnist::readImage(imgfile, imgndx);
    // center star uvec is implicit in the image
    // get other star uvecs from image data
    uvecs.zeros(100,3);
    int uvecsndx = 0;
    for (int axjndx = 0; axjndx < 28; ++axjndx) {
        for (int axindx = 0; axindx < 28; ++axindx) {
            if (image(axjndx, axindx) > 0) { // there's a star inside axjndx, axindx
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

void stars::Image::replaceAxjAxiImage(arma::mat& axjAxiImage, stars::Sky& sky, int starndx) {
    // get uvec for centerstar
    stars::Star centerStar = sky.stars[starndx];
    double x = centerStar.x;
    double y = centerStar.y;
    double z = centerStar.z;
    // get other stars in image
    std::vector<int> starndxs = sky.starsNearPoint(x, y, z);
    uvecs.zeros(100,3);
    int uvecsndx = 0;
    for (auto ndx : starndxs) {
        x = sky.stars[ndx].x;
        y = sky.stars[ndx].y;
        uvecs(uvecsndx,0) = x;
        uvecs(uvecsndx,1) = y;
        uvecs(uvecsndx,2) = std::sqrt(1 - x*x - y*y);
        ++uvecsndx;
    }
    // update image uvecs
}
