/// *sky*
///
/// sky representation as pointing vectors, with methods to get the stars near an arbitrary point.
///

#ifndef STARS_H
#define STARS_H

#include <cereal/access.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <string>
#include <vector>
#include "../libstarid/Eigen/Core"
#include <fstream>

namespace starid {

class float_int_table {

public:

    void addPair(double newFloat, int newInt);

    void sort();

    std::vector<int> findInts(double lowerFloat, double upperFloat);

private:

    std::vector<std::pair<double,int>> floatIntTable;

    friend class cereal::access;
    template <class Archive> void serialize(Archive& ar) {
        ar(floatIntTable);
    }

};

struct Star {
    int starndx;
    int skymap_number;
    double mv;
    double x;
    double y;
    double z;
    template <class Archive> void serialize(Archive& ar) {
        ar(starndx, skymap_number, mv, x, y, z);
    }
};

class Sky {

public:

    std::vector<starid::Star> stars;
    std::vector<std::string> catalog_lines;

    void init(std::string fcatalog);

    std::vector<int> starsNearPoint(double x, double y, double z);

    void status();

private:

    double t;
    std::string fcatalog;
    starid::float_int_table xtable;
    starid::float_int_table ytable;
    starid::float_int_table ztable;

    std::vector<int> starsInRing(double p, double radius, starid::float_int_table& table);

    friend class cereal::access;
    template <class Archive> void serialize(Archive& ar) {
        ar(stars, xtable, ytable, ztable);
    }
};

struct star_record {
    double mv1;
    std::string iau_identifier;
    std::string star_name;
    std::string variablestar_name;
    int skymap_number;
    int hd_number;
    int sao_number;
    int dm_number;
    int hr_number;
    int wds_number;
    int ppm_number;
    bool blended_position;
    double rah;
    double ram;
    double ras;
    double decd;
    double decm;
    double decs;
    double pmra_arcsec_per_year;
    double pmdec_arcsec_per_year;
    double decsign;
    double pmdecsign;
    std::string fileLine;
};

class star_catalog {

public:

    star_catalog(std::string fcat);
    std::vector<starid::star_record> star_records;
    int dimStars;

};

using image_matrix = Eigen::Matrix<double, 28, 28>;
using ang_seq_vec = Eigen::Matrix<double, 36, 1>;

class pointing_vectors {

public:

    /// *new image matrix* create an axi axj image matrix for the star, with a random yaw
    ///
    static image_matrix new_image_matrix(int starndx, starid::Sky &sky);

    /// *new yaw series* yaw series for use by recurrent networks
    ///
    static ang_seq_vec new_ang_seq_vec(int starndx, starid::Sky &sky);

    /// *get pointing vectors* get pointing vector representation of an image
    ///
    static Eigen::MatrixXd get_pvecs_from_imgmat(image_matrix &imgmat);


private:

    static Eigen::Matrix3d rotation_matrix(Eigen::Vector3d &pointing);

    static Eigen::Vector3d crossprod(Eigen::Vector3d &u, Eigen::Vector3d &v);

};

}

#endif

