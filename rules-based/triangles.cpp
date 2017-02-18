#include "triangles.h"

rules::Triangles::Triangles(stars::Image& image, rules::PairsOverWholeSky& pairs, double tolrad) :
    all_pairs(pairs), image(image), tol_radius(tolrad) {
}

int rules::Triangles::identifyCentralStar() {
    std::unordered_map<int, int> curstars;
    int num_stars = image.uvecs.n_rows;
    arma::vec uveca = arma::trans(image.uvecs.row(0)); // star a
    for (int ndxb = 1; ndxb < num_stars; ++ndxb) {
        arma::vec uvecb = arma::trans(image.uvecs.row(ndxb)); // star b
        for (int ndxc = 1; ndxc < num_stars; ++ndxc) {
            if (ndxc == ndxb) continue;
            std::vector<double> angsc;
            arma::vec uvecc = arma::trans(image.uvecs.row(ndxc)); // star c
            angsc.push_back(std::acos(arma::dot(uveca, uvecb)));
            angsc.push_back(std::acos(arma::dot(uvecb, uvecc)));
            angsc.push_back(std::acos(arma::dot(uvecc, uveca)));
            bool skipc = false;
            double min_ang = 3000.0 * M_PI / 648000.0;
            if (angsc[0] < min_ang) skipc = true; // ab
            if (angsc[1] < min_ang) skipc = skipc; // bc allow
            if (angsc[2] < min_ang) skipc = true; // ca
            if (std::abs(angsc[0]-angsc[1]) < min_ang) skipc = true; // ab-bc
            if (std::abs(angsc[0]-angsc[2]) < min_ang) skipc = true; // ab-ca
            if (std::abs(angsc[1]-angsc[2]) < min_ang) skipc = true; // bc-ca
            if (skipc) continue;
            Triangle abc(angsc[0], angsc[1], angsc[2], tol_radius, all_pairs);
            for (int ndxd = 1; ndxd < num_stars; ++ndxd) {
                if (ndxd == ndxb || ndxd == ndxc) continue;
                std::vector<double> angsd = angsc;
                arma::vec uvecd = arma::trans(image.uvecs.row(ndxd)); // star d
                angsd.push_back(std::acos(arma::dot(uvecd, uveca)));
                angsd.push_back(std::acos(arma::dot(uvecd, uvecb)));
                angsd.push_back(std::acos(arma::dot(uvecd, uvecc)));
                bool skipd = false;
                if (angsd[3] < min_ang) skipd = skipd; // da allow
                if (angsd[4] < min_ang) skipd = true; // db
                if (angsd[5] < min_ang) skipd = true; // dc
                if (std::abs(angsd[4]-angsd[5]) < min_ang) skipd = true; // db-dc
                if (skipd) continue;
                Triangle abd = abc;
                abd.bd_da(angsd[4], angsd[3], tol_radius, all_pairs);
                Triangle adc = abd;
                adc.dc_ca(angsd[5], abc, tol_radius, all_pairs);
                int zzz = 1;
            }
        }
        std::unordered_map<int, int> merged; // = ad.stars_in_three_sides(ab, ac);
        update_stars(curstars, merged);
    }

    std::map<int, int> starsa;
    std::multimap<int, int, std::greater<int>> starsb;
    for (auto it = curstars.begin(), end = curstars.end(); it != end; ++it) {
        starsa.emplace(it->first, it->second);
        starsb.emplace(it->second, it->first);
    }
    return -1;
}

void rules::Triangles::update_stars(std::unordered_map<int, int>& stars1, const std::unordered_map<int, int>& stars2){
    for (auto it2 = stars2.begin(), end = stars2.end(); it2 != end; ++it2) {
        auto it1 = stars1.find(it2->first);
        if (it1 != stars1.end()) {
            ++it1->second;
        } else {
            stars1.emplace(it2->first, 1);
        }
    }
}





