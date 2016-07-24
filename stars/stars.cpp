#include "stars.h"
#include <cassert>

stars::Star::Star()
    : iau_identifier(""),
      star_name(""),
      variablestar_name(""),
      skymap_number(0),
      hd_number(0),
      sao_number(0),
      dm_number(0),
      hr_number(0),
      wds_number(0),
      ppm_number(0),
      blended_position(false),
      mv1(100.0),
      ra_degrees(0.0),
      dec_degrees(0.0),
      ra(0.0),
      dec(0.0),
      uv()
{}

stars::Stars::Stars()
{
    arma::arma_rng::set_seed_random();
    f_catalog = "../../SKYMAP_SKY2000_V5R4.txt";
    t = 0.0;
    mv = 6.5;
    fov = 4.0 * arma::datum::pi / 180.0;

    std::ifstream catfile (f_catalog);
    int ndx {0};
    int dim_stars {0};
    int error_stars {0};
    if (catfile.is_open()) {
        std::string line;
        while (std::getline(catfile, line)) {
            try {
                Star star;
                try {star.mv1 = std::stof(line.substr(232,6));} catch(...){}
                if (star.mv1 > mv) {
                    ++dim_stars;
                    continue;
                }
                star.iau_identifier = line.substr(0,27);
                try {star.star_name = line.substr(98,10);} catch(...){}
                try {star.variablestar_name = line.substr(108,10);} catch(...){}
                star.skymap_number = std::stoi(line.substr(27,8));
                try {star.hd_number = std::stoi(line.substr(35,8));} catch(...){}
                try {star.sao_number = std::stoi(line.substr(43,7));} catch(...){}
                try {star.dm_number = std::stoi(line.substr(50,13));} catch(...){}
                try {star.hr_number = std::stoi(line.substr(63,4));} catch(...){}
                try {star.wds_number = std::stoi(line.substr(67,6));} catch(...){}
                try {star.ppm_number = std::stoi(line.substr(83,7));} catch(...){}
                try {star.blended_position = std::stoi(line.substr(146,1));} catch(...){}
                double rah = std::stof(line.substr(118,2));
                double ram = std::stof(line.substr(120,2));
                double ras = std::stof(line.substr(122,7));
                double decd = std::stof(line.substr(130,2));
                double decm = std::stof(line.substr(132,2));
                double decs = std::stof(line.substr(134,6));
                double pmra_arcsec_per_year = 15.0 * std::stof(line.substr(149,8));
                double pmdec_arcsec_per_year = std::stof(line.substr(158,7));
                double decsign = 1.0;
                double pmdecsign = 1.0;
                if (line.substr(129,1) == "-") decsign = -1.0;
                if (line.substr(157,1) == "-") pmdecsign = -1.0;
                star.ra_degrees = 15.0 * (rah + ram/60.0 + ras/3600.0);
                star.dec_degrees = decsign * (decd + decm/60.0 + decs/3600.0);
                star.ra_degrees += (t * pmra_arcsec_per_year) / 3600.0;
                star.dec_degrees += (t * pmdecsign * pmdec_arcsec_per_year) / 3600.0;
                assert (star.ra_degrees >= 0.0 && star.ra_degrees <= 360.0);
                assert (star.dec_degrees >= -90.0 && star.dec_degrees <= 90.0);

                double ra = star.ra_degrees * arma::datum::pi / 180.0;
                double dec = star.dec_degrees * arma::datum::pi / 180.0;
                star.ra = ra;
                star.dec = dec;
                star.uv.set_size(3);
                star.uv(0) = cos(ra)*cos(dec);
                star.uv(1) = sin(ra)*cos(dec);
                star.uv(2) = sin(dec);
                star.uv = normalise(star.uv);
                assert(norm(star.uv) - 1.0 < 1e-10);

                std::pair<double,int> xpair {star.uv(0), ndx};
                std::pair<double,int> ypair {star.uv(1), ndx};
                std::pair<double,int> zpair {star.uv(2), ndx};
                xtable.push_back(xpair);
                ytable.push_back(ypair);
                ztable.push_back(zpair);
                starsvec.push_back(star);
                ++ndx;
            } catch (...) {
                ++error_stars;
            }
        }
        catfile.close();
//        std::cout << "stars " << ndx << " dim stars " << dim_stars << " error_stars " << error_stars << "\n";
    } else {
        std::cout << "catalog file not found" << "\n";
    }
    std::sort(xtable.begin(), xtable.end());
    std::sort(ytable.begin(), ytable.end());
    std::sort(ztable.begin(), ztable.end());
}
//double UnixTimeToJ2000Offset = 946684800.0;
//std::chrono::time_point<std::chrono::system_clock> tcurrent {std::chrono::system_clock::now()};
//double t {(double(std::chrono::system_clock::to_time_t(tcurrent)) - UnixTimeToJ2000Offset) / 31557600.0}; // julian years

std::vector<int> stars::Stars::StarsNearPoint(arma::vec& uv, const double radius) {
    std::vector<int> xring = StarsInRing(uv(0), radius, xtable);
    std::vector<int> yring = StarsInRing(uv(1), radius, ytable);
    std::vector<int> zring = StarsInRing(uv(2), radius, ztable);
    std::vector<int> xy;
    std::set_intersection(xring.begin(), xring.end(), yring.begin(), yring.end(), std::back_inserter(xy));
    std::vector<int> xyz;
    std::set_intersection(xy.begin(), xy.end(), zring.begin(), zring.end(), std::back_inserter(xyz));
    std::vector<int> ndxs;
    for (uint i = 0; i < xyz.size(); ++i) {
        arma::vec uv2 = starsvec[xyz[i]].uv;
        if (acos(arma::dot(uv,uv2)) <= radius) {
            ndxs.push_back(xyz[i]);
        }
    }
    return ndxs;
}

std::vector<int> stars::Stars::StarsInRing(double p, double radius, std::vector<std::pair<double,int>> &table) {
    double pmin, pmax;
    if (p >= cos(radius)) {
        pmin = p*cos(radius) - sqrt(1-(p*p))*sin(radius);
        pmax = 1.0;
    } else if (p <= -cos(radius)) {
        pmin = -1.0;
        pmax = p*cos(radius) + sqrt(1-(p*p))*sin(radius);
    } else {
        pmin = p*cos(radius) - sqrt(1-(p*p))*sin(radius);
        pmax = p*cos(radius) + sqrt(1-(p*p))*sin(radius);
    }
    assert (pmin >= -1.0 && pmax <= 1.0);
    auto itlow = std::lower_bound(table.begin(), table.end(), std::make_pair(pmin, 0));
    auto ithi = std::upper_bound(table.begin(), table.end(), std::make_pair(pmax, 0));
    std::vector<int> ring;
    for (auto it = itlow; it <= ithi; ++it) {
        auto tablerow = *it;
        ring.push_back(tablerow.second);
    }
    std::sort(ring.begin(),ring.end());
    return ring;
}

void stars::Stars::Status() {
    std::cout << "number of stars " << starsvec.size() << "\n";
}
