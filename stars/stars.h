#ifndef STARS_H
#define STARS_H

#include <armadillo>

namespace stars {

struct Star {
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
    double mv1;
    double ra_degrees;
    double dec_degrees;
    double ra;
    double dec;
    arma::vec uv;
    Star();
};

class Stars {

public:

    std::vector<stars::Star> starsvec;

    void Init(std::string f_catalog, double mv, double fov);

    std::vector<int> StarsNearPoint(arma::vec& uv, const double radius);
    void Status();

private:

    double t;
    double mv;
    double fov;
    std::string f_catalog;
    std::vector<std::pair<double,int>> xtable;
    std::vector<std::pair<double,int>> ytable;
    std::vector<std::pair<double,int>> ztable;
    std::vector<int> StarsInRing(double p, double radius, std::vector<std::pair<double,int>> &table);

};

}

#endif

