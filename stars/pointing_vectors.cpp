#include "pointing_vectors.h"
#include "globals.h"
#include <cmath>
#include <random>

std::random_device r;
std::default_random_engine e1(r());
std::uniform_real_distribution<double> unitscatter(0, 1);

starid::image_matrix starid::pointing_vectors::new_image_matrix(int starndx, starid::Sky &sky) {
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

    double yaw = unitscatter(e1) * 2 * starid::pi;
    Eigen::Matrix3d attitude = rotation_matrix(pointing);
    pvecs = (attitude.transpose() * pvecs.transpose()).transpose();

    for (int ndx = 0; ndx < pvecsndx; ++ndx) {
        double x = std::cos(yaw) * pvecs(ndx,0) - std::sin(yaw) * pvecs(ndx,1);
        double y = std::sin(yaw) * pvecs(ndx,0) + std::cos(yaw) * pvecs(ndx,1);
        double axi = x + starid::image_radius_unit_vector_plane;
        double axj = -y + starid::image_radius_unit_vector_plane;
        int axindx = std::floor( axi / starid::image_pixel_unit_vector_plane );
        int axjndx = std::floor( axj / starid::image_pixel_unit_vector_plane );
        if (axjndx < 0 || axjndx > 27) continue;
        if (axindx < 0 || axindx > 27) continue;
        imgmat(axjndx, axindx) = 255.0;
    }

    return imgmat;
}

Eigen::MatrixXd starid::pointing_vectors::get_pvecs_from_imgmat(starid::image_matrix &imgmat) {
    Eigen::MatrixXd pvecs = Eigen::MatrixXd::Zero(100,3);
    pvecs.row(0) << 0.0, 0.0, 1.0;
    int pvecsndx = 1;
    for (int axjndx = 0; axjndx < 28; ++axjndx) {
        for (int axindx = 0; axindx < 28; ++axindx) {
            if (imgmat(axjndx, axindx) > 0) { // there's a star inside axjndx, axindx
                double x = starid::image_pixel_unit_vector_plane * ( -13.5 + (double)axindx );
                double y = starid::image_pixel_unit_vector_plane * ( +13.5 - (double)axjndx );
                pvecs.row(pvecsndx) << x, y, std::sqrt(1 - x*x - y*y);
                ++pvecsndx;
            }
        }
    }
    pvecs.conservativeResize(pvecsndx, 3);
    return pvecs;
}

Eigen::Matrix3d starid::pointing_vectors::rotation_matrix(Eigen::Vector3d &bodyz) {
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

Eigen::Vector3d starid::pointing_vectors::crossprod(Eigen::Vector3d &u, Eigen::Vector3d &v) {
    Eigen::Vector3d result;
    result(0) = u(1)*v(2) - u(2)*v(1);
    result(1) = u(2)*v(0) - u(0)*v(2);
    result(2) = u(0)*v(1) - u(1)*v(0);
    return result;
}
