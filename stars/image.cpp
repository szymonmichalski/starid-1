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
    double x, y, x2, y2, yaw, xcf, ycf, zcf;
    // get uvec for centerstar
    xcf = sky.stars[starndx].x;
    ycf = sky.stars[starndx].y;
    zcf = sky.stars[starndx].z;
    // get uvecs of other stars in image
    std::vector<int> starndxs = sky.starsNearPoint(xcf, ycf, zcf);
    uvecs.zeros(100,3);
    int uvecsndx = 0;
    for (auto ndx : starndxs) {
        xcf = sky.stars[ndx].x;
        ycf = sky.stars[ndx].y;
        zcf = sky.stars[ndx].z;
        x = 0.0; // todo
        y = 0.0;
        yaw = unitscatter(e1) * 360.0;
        x2 = (std::cos(yaw) * x) - (std::sin(yaw) * y);
        y2 = (std::sin(yaw) * x) + (std::cos(yaw) * y);
        uvecs(uvecsndx,0) = x2;
        uvecs(uvecsndx,1) = y2;
        uvecs(uvecsndx,2) = std::sqrt(1 - x2*x2 - y2*y2);
        ++uvecsndx;
    }
    uvecs.shed_rows(uvecsndx, 99);
    // update axjaxiimage
    axjAxiImage.zeros();
    for (int ndx = 0; ndx < uvecsndx; ++ndx) {
        x = uvecs(ndx,0);
        y = uvecs(ndx,1);
        int axjndx = 0;
        int axindx = 0;
        axjAxiImage(axjndx, axindx) = 255.0;
    }
}


