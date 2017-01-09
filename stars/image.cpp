#include "image.h"
#include <cmath>

void stars::Image::readMnistImage(std::string& imgfile, int imgndx) {

    Eigen::Matrix<double, 28, 28> image = data::Mnist::readImage(imgfile, imgndx);
    double fovLen = std::atan(4.0 * arma::datum::pi / 180.0);
    double pixelLen = fovLen / 14.0;
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_real_distribution<double> unitscatter(0, 1);
    uvecs.zeros(100,3);

    // central star is implicit in the image
    uvecs(0,0) = 0.0;
    uvecs(0,1) = 0.0;
    uvecs(0,2) = 1.0;

    // get other stars from the image data
    int uvecsndx = 1;
    for (int axjndx = 0; axjndx < 28; ++axjndx) {
        for (int axindx = 0; axindx < 28; ++axindx) {
            if (image(axjndx, axindx) > 0) { // there's a star inside axjndx, axindx
                double x = (-14.0 + (double)axindx + unitscatter(e1)) * pixelLen;
                double y = (14.0 - (double)axjndx - unitscatter(e1)) * pixelLen;
                uvecs(uvecsndx,0) = x;
                uvecs(uvecsndx,1) = y;
                uvecs(uvecsndx,2) = std::sqrt(1 - x*x - y*y);
                ++uvecsndx;
            }
        }
    }
    uvecs.shed_rows(uvecsndx, 99);
}
