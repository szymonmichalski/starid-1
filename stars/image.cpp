#include "image.h"

void stars::Image::useMnistImage(int imgndx) {

    Eigen::Matrix<double, 28, 28> image = data::Mnist::readImage(imgndx);

    double centerStarBound = 10 * (arma::datum::pi / 648e3); // ten arcseconds in radians
    double fov = 4.0 * arma::datum::pi / 180.0;
    double pixelAngle = fov / 14.0;
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_real_distribution<double> uniform_dist(0, 1);

    uvecs.zeros(100,3);
    int uvecsndx = 0;
    for(int r = 0; r < 28; ++r) {
        for(int c = 0; c < 28; ++c) {
            if (image(r,c) > 0) {
                double h = pixelAngle * (r - 14.0);
                double v = pixelAngle * (c - 14.0);
                if (abs(h) > centerStarBound || abs(v) > centerStarBound) { // don't scatter center star
                    double dh = uniform_dist(e1) * pixelAngle;
                    double dv = uniform_dist(e1) * pixelAngle;
                    if (h < 0) h += -dh; else h += dh; // floor was used in creating image
                    if (v < 0) v += -dv; else v += dv; // star could be anywhere in a pixel
                }
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

