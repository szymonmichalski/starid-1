/// *star identifier*
///
/// find star triangles in the image, and candidate stars that meet the constraints implicit within the triangle. these constraints are effectively the rules for candidate stars. for example, if a triangle consists of star pairs ab and bc, then the third side is ac.
///

#ifndef STARIDENTIFIER_H
#define STARIDENTIFIER_H

#include "triangle.h"
#include "triangle_side.h"
#include "pairs.h"
#include "globals.h"
#include "pointing_vectors.h"
#include <Eigen/Core>
#include <unordered_map>
#include <map>

namespace id {

class star_identifier
{

public:

    star_identifier(stars::image_matrix &imgmat, stars::Pairs &pairs);

    /// *identify central star* this is the main function
    ///
    int id(int teststar = -1);

private:

    bool get_angs_c();
    bool get_angs_d();
    stars::Pairs pairs;
    Eigen::MatrixXd pvecs;
    double tolerance;
    double min_ang;
    std::vector<double> angs_c;
    std::vector<double> angs_d;
    Eigen::Vector3d uveca;
    Eigen::Vector3d uvecb;
    Eigen::Vector3d uvecc;
    Eigen::Vector3d uvecd;
    int ndxb, ndxc, ndxd;
    int teststar;

};

}

#endif
