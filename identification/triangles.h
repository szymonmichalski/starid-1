/// *star identifier*
///
/// find star triangles in the image, and candidate stars that meet the constraints implicit within the triangle. these constraints are effectively the rules for candidate stars. for example, if a triangle consists of star pairs ab and bc, then the third side is ac.
///

#ifndef STARIDENTIFIER_H
#define STARIDENTIFIER_H

#include "sky.h"
#include "globals.h"
#include "../libstarid/Eigen/Core"
#include <unordered_map>
#include <map>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/tuple.hpp>
#include <cereal/types/unordered_map.hpp>

namespace starid {

class Pairs {

public:

    /// *pairs map* each star is a map key whose value is a map of star keys it pairs with.
    ///
    std::unordered_map<int, std::unordered_map<int, int>> pairs_map(double angle, double tol_radius);

    /// *init* creates the pairs data structures for all star pairs with a separation less than maximum angle.
    ///
    void init(double max_ang, starid::Sky& sky);

private:

    starid::float_int_table angletable; // angle, starpairs ndx

    std::vector<std::tuple<double, int, int>> starpairs; // angle, catndx1, catndx2

    std::unordered_map<std::string, int> starpairs_map; // starpairkey, starpairsndx

    std::string pairsKey(int catndx1, int catndx2); // hash key

    friend class cereal::access;
    template <class Archive> void serialize(Archive& ar) {
        ar(starpairs, starpairs_map, angletable);
    }
};

class triangles
{

public:

    triangles(starid::image_matrix &imgmat, starid::Pairs &pairs);

    /// *identify central star* this is the main function
    ///
    int id(int teststar = -1);

private:

    bool get_angs_c();
    bool get_angs_d();
    starid::Pairs pairs;
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

class TriangleSide {

public:

    /// *stars* each star is a map key whose value is a map of star keys it pairs with
    ///
    std::unordered_map<int, std::unordered_map<int, int>> stars;

    /// *trim pairs* remove pairs that have value zero or are no longer stars. then remove stars that have no pairs.
    ///
    void trim_pairs();

    /// *append iterations* append the iterations contained in another side
    ///
    void append_iterations(TriangleSide &side);

    std::vector<int> log_star_count;
    std::vector<int> log_pair_count;
    std::vector<bool> log_teststar;
    int teststar;
    bool has_teststar;

    TriangleSide(double ang,
                 double tolerance,
                 starid::Pairs& pairs,
                 int teststar);

    TriangleSide(int teststar);

    std::map<int, int> summary();
    bool check_teststar(int teststar);
    int pair_count();

private:

};

class Triangle
{

public:

    /// *close loops abca* travel around sides connecting by pairs.
    ///
    void close_loops_abca();

    /// *close loops abda* travel around sides connecting by pairs.
    ///
    void close_loops_abda(std::vector<Triangle> &triangles);

    Triangle(double ang1,
             double ang2,
             double ang3,
             double tolerance,
             starid::Pairs& pairs,
             int teststar,
             Eigen::Vector3d vecstar3);

    starid::TriangleSide side1;
    starid::TriangleSide side2;
    starid::TriangleSide side3;
    int loops_cnt;
    int teststar;
    double tolerance;
    starid::Pairs &pairs;
    Eigen::Vector3d vecstar3;

private:

};

}

#endif
