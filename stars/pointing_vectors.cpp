#include "pointing_vectors.h"
#include "globals.h"
#include <cmath>
#include <random>

std::random_device r;
std::default_random_engine e1(r());
std::uniform_real_distribution<double> unitscatter(0, 1);

stars::image_matrix stars::pointing_vectors::new_image_matrix(stars::Sky &sky, int starndx) {
    using namespace Eigen;
    image_matrix imgmat = image_matrix::Zero();

    Vector3d pointing;
    pointing << sky.stars[starndx].x, sky.stars[starndx].y, sky.stars[starndx].z;
    std::vector<int> starndxs = sky.starsNearPoint(pointing(0), pointing(1), pointing(2));

    Eigen::MatrixXd pvecs = Eigen::MatrixXd::Zero(100,3);
    int pvecsndx = 0;
    for (auto ndx : starndxs) {
        pvecs.row(pvecsndx) << sky.stars[ndx].x, sky.stars[ndx].y, sky.stars[ndx].z;
        ++pvecsndx;
    }
    pvecs.conservativeResize(pvecsndx, 3);

    double yaw = unitscatter(e1) * 2 * stars::pi;
    Eigen::Matrix3d attitude = rotation_matrix(pointing);
    pvecs = (attitude.transpose() * pvecs.transpose()).transpose();

    for (int ndx = 0; ndx < pvecsndx; ++ndx) {
        double x = std::cos(yaw) * pvecs(ndx,0) - std::sin(yaw) * pvecs(ndx,1);
        double y = std::sin(yaw) * pvecs(ndx,0) + std::cos(yaw) * pvecs(ndx,1);
        double axi = x + stars::image_radius_unit_vector_plane;
        double axj = -y + stars::image_radius_unit_vector_plane;
        int axindx = std::floor( axi / stars::image_pixel_unit_vector_plane );
        int axjndx = std::floor( axj / stars::image_pixel_unit_vector_plane );
        if (axjndx < 0 || axjndx > 27) continue;
        if (axindx < 0 || axindx > 27) continue;
        imgmat(axjndx, axindx) = 255.0;
    }

    return imgmat;
}

Eigen::MatrixXd stars::pointing_vectors::get_pvecs_from_imgmat(stars::image_matrix &imgmat) {
    Eigen::MatrixXd pvecs = Eigen::MatrixXd::Zero(100,3);
    pvecs.row(0) << 0.0, 0.0, 1.0;
    int pvecsndx = 1;
    for (int axjndx = 0; axjndx < 28; ++axjndx) {
        for (int axindx = 0; axindx < 28; ++axindx) {
            if (imgmat(axjndx, axindx) > 0) { // there's a star inside axjndx, axindx
                double x = stars::image_pixel_unit_vector_plane * ( -13.5 + (double)axindx );
                double y = stars::image_pixel_unit_vector_plane * ( +13.5 - (double)axjndx );
                pvecs.row(pvecsndx) << x, y, std::sqrt(1 - x*x - y*y);
                ++pvecsndx;
            }
        }
    }
    pvecs.conservativeResize(pvecsndx, 3);
    return pvecs;
}

stars::image_matrix stars::pointing_vectors::read_image_matrix(std::string &imgfile, int imgndx) {
    image_matrix image;
    std::ifstream file (imgfile, std::ios::binary);
    if (file.is_open())
    {
        int magnumimg, imgcnt, axjcnt, axicnt; // local variables, function is static
        file.read((char*) &magnumimg, sizeof(magnumimg));
        magnumimg = reverseInt(magnumimg);
        file.read((char*) &imgcnt, sizeof(imgcnt));
        imgcnt = reverseInt(imgcnt);
        file.read((char*) &axjcnt, sizeof(axjcnt));
        axjcnt = reverseInt(axjcnt); // 28
        file.read((char*) &axicnt, sizeof(axicnt));
        axicnt = reverseInt(axicnt); // 28

        int curimgndx = 0;
        while (curimgndx < imgndx) {
            for (int axjndx = 0; axjndx < 28; ++axjndx) { // inverted-y-like, row-like
                for (int axindx = 0; axindx < 28; ++axindx) { // x-like, col-like
                    unsigned char temp = 0;
                    file.read((char*) &temp, sizeof(temp));
                }
            }
            ++curimgndx;
        }
        // (axjndx inverted-y-like row-like), (axindx x-like col-like) plane
        for (int axjndx = 0; axjndx < 28; ++axjndx) { // inverted-y-like, row-like
            for (int axindx = 0; axindx < 28; ++axindx) { // x-like, col-like
                unsigned char temp = 0;
                file.read((char*) &temp, sizeof(temp));
                image(axjndx, axindx) = (double)temp;
            }
        }
    }
    return image;
}

Eigen::Matrix3d stars::pointing_vectors::rotation_matrix(Eigen::Vector3d &bodyz) {
    using namespace Eigen;
    Matrix3d rm = Matrix3d::Identity(3,3);
    Vector3d icrfz(0.0, 0.0, 1.0);
    Vector3d bodyx = crossprod(bodyz, icrfz);
    Vector3d bodyy = crossprod(bodyz, bodyx);
    rm.col(0) = bodyx.normalized();
    rm.col(1) = bodyy.normalized();
    rm.col(2) = bodyz.normalized();
    return rm;
}

Eigen::Vector3d stars::pointing_vectors::crossprod(Eigen::Vector3d &u, Eigen::Vector3d &v) {
    Eigen::Vector3d result;
    result(0) = u(1)*v(2) - u(2)*v(1);
    result(1) = u(2)*v(0) - u(0)*v(2);
    result(2) = u(0)*v(1) - u(1)*v(0);
    return result;
}

int stars::pointing_vectors::reverseInt (int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return((int) ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}



// following still need to be switched from armadillo to eigen

//void stars::pointing_vectors::write_images_container(std::string filename, std::vector<arma::mat> &images) {
//    std::ofstream file (filename, std::ios::binary);
//    int rev_magnumimg = reverseInt(magnumimg);
//    int rev_imgcnt = reverseInt(imgcnt);
//    int rev_axjcnt = reverseInt(axjcnt);
//    int rev_axicnt = reverseInt(axicnt);
//    if (file.is_open()) {
//        file.write((char*) &rev_magnumimg, sizeof(rev_magnumimg));
//        file.write((char*) &rev_imgcnt, sizeof(rev_imgcnt));
//        file.write((char*) &rev_axjcnt, sizeof(rev_axjcnt));
//        file.write((char*) &rev_axicnt, sizeof(rev_axicnt));
//        for (int imgndx = 0; imgndx < imgcnt; ++imgndx) {
//            arma::mat image = images[imgndx];
//            for (int axjndx = 0; axjndx < axjcnt; ++axjndx) {
//                for(int axindx = 0; axindx < axicnt; ++axindx) {
//                    unsigned char temp = (unsigned char) image(axjndx, axindx);
//                    file.write((char*) &temp, sizeof(temp));
//                }
//            }
//        }
//    }
//}

//void stars::pointing_vector::write_labels_container(std::string filename, arma::colvec &labels) {
//    std::ofstream file (filename, std::ios::binary);
//    int rev_magnumlab = reverseInt(magnumlab);
//    int rev_imgcnt = reverseInt(imgcnt);
//    if (file.is_open()) {
//        file.write((char*) &rev_magnumlab, sizeof(rev_magnumlab));
//        file.write((char*) &rev_imgcnt, sizeof(rev_imgcnt));
//        for(int imgndx = 0; imgndx < imgcnt; ++imgndx) {
//            unsigned char temp = (unsigned char) labels(imgndx);
//            file.write((char*) &temp, sizeof(temp));
//        }
//    }
//}

//void stars::pointing_vector::read_labels_container(std::string filename, arma::colvec &labels) {
//    std::ifstream file (filename, std::ios::binary);
//    if (file.is_open()) {
//        file.read((char*) &magnumlab, sizeof(magnumlab));
//        magnumlab = reverseInt(magnumlab);
//        file.read((char*) &imgcnt, sizeof(imgcnt));
//        imgcnt = reverseInt(imgcnt);
//        for(int imgndx = 0; imgndx < imgcnt; ++imgndx) {
//            unsigned char temp = 0;
//            file.read((char*) &temp, sizeof(temp));
//            labels(imgndx)= (double) temp;
//        }
//    }
//}

//std::string a = "images_a";
//std::string b = "images_b";
//doMnist(60000, datadir, a, sky);
//doMnist(10000, datadir, b, sky);
//void doMnist(int imgCnt, std::string& datadir, std::string& filename, stars::Sky& sky) {
//    data::Mnist mnist;
//    std::vector<arma::mat> axjAxiImages;
//    arma::colvec labels = arma::zeros<arma::colvec>(imgCnt);
//    mnist.readAxjAxiImages(std::string(datadir + filename + "1.mnist"), axjAxiImages); // 28x28ximgCnt images
//    mnist.readLabels(std::string(datadir + filename + "2.mnist"), labels); // imageCntx1 labels
//    for (int starSetNdx = 0; starSetNdx < imgCnt/10; ++starSetNdx) {
//        for (int starndx = 0; starndx < 10; ++starndx) {
//            arma::mat axjAxiImage = axjAxiImages[10*starSetNdx + starndx]; // get current image
//            stars::Image image;
//            image.axjAxiImageUpdate(axjAxiImage, sky, starndx);
//            labels(10*starSetNdx + starndx) = (double) starndx; // update current label
//            axjAxiImages[10*starSetNdx + starndx] = axjAxiImage; // update current image
//        }
//    }
//    mnist.writeImages(std::string(datadir + filename + "1.mnist"), axjAxiImages);
//    mnist.writeLabels(std::string(datadir + filename + "2.mnist"), labels);
//}
