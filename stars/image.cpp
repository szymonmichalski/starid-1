#include "image.h"

void stars::Image::useMnistImage(int imgndx) {

    Eigen::Matrix<double, 28, 28> image = data::Mnist::readImage(imgndx);

    double fov = 4.0 * arma::datum::pi / 180.0;

    uvecs.zeros(100,3);
    int uvecsndx = 0;
    for(int r = 0; r < 28; ++r) {
        for(int c = 0; c < 28; ++c) {
            if (image(r,c) > 0) {
                double h = fov * (r - 14.0) / 14.0;
                double v = fov * (c - 14.0) / 14.0;
                double x = tan(h);
                double y = tan(v);
                double z = 1.0;
                double len = std::sqrt( x*x + y*y + z*z );
                uvecs(uvecsndx,0) = x/len;
                uvecs(uvecsndx,1) = y/len;
                uvecs(uvecsndx,2) = z/len;
                ++uvecsndx;
            }
        }
    }
    uvecs.shed_rows(uvecsndx, 99);
}

//    l1_hv.col(0) = arma::atan(l1_uvec.col(0) / l1_uvec.col(2));
//    l1_hv.col(1) = arma::atan(l1_uvec.col(1) / l1_uvec.col(2));
//        int row = 14 + floor(14 * l1_hv(i,0) / fov);
//        int col = 14 + floor(14 * l1_hv(i,1) / fov);

