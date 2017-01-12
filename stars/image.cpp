#include "image.h"
#include <cmath>
#include "globals.h"

void stars::Image::readMnistImage(std::string& imgfile, int imgndx) {

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_real_distribution<double> unitscatter(0, 1);

    Eigen::Matrix<double, 28, 28> image = data::Mnist::readImage(imgfile, imgndx);
    uvecs.zeros(100,3);
    uvecs(0,0) = 0.0; // central star is implicit in the image
    uvecs(0,1) = 0.0;
    uvecs(0,2) = 1.0;

    // get other stars from the image data
    int uvecsndx = 1;
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
