/// *pointing vectors*
///
/// star representations as pointing vectors and binary images container on disk
///
#ifndef IMAGE_H
#define IMAGE_H

#include "sky.h"
#include "../lib/Eigen/Core"
#include <fstream>

namespace starid {

using image_matrix = Eigen::Matrix<double, 28, 28>;

class pointing_vectors {

public:

    /// *new image matrix* create an axi axj image matrix for the star, with a random yaw
    ///
    static image_matrix new_image_matrix(int starndx, starid::Sky &sky);

    /// *get pointing vectors* get pointing vector representation of an image
    ///
    static Eigen::MatrixXd get_pvecs_from_imgmat(image_matrix &imgmat);


private:

    static Eigen::Matrix3d rotation_matrix(Eigen::Vector3d &pointing);

    static Eigen::Vector3d crossprod(Eigen::Vector3d &u, Eigen::Vector3d &v);

};

}

#endif
