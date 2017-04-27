#include "star_identifier.h"

id::star_identifier::star_identifier(stars::image_matrix &imgmat, stars::Pairs &pairs) : pairs(pairs)
{
    pvecs = stars::pointing_vectors::get_pvecs_from_imgmat(imgmat);
    double epsilon = 0.0;
    tolerance = (2.0 * std::sqrt(500.0*500.0 + 500.00*500.0) + epsilon) * stars::arcseconds_to_radians;
}

int id::star_identifier::id(int teststar) {

    std::vector<TriangleSide> abs;
    for (ndxb = 1; ndxb < pvecs.rows(); ++ndxb) {

        uveca = pvecs.row(0);
        uvecb = pvecs.row(ndxb);
        TriangleSide ab(std::acos(uveca.transpose() * uvecb), tolerance, pairs, teststar);

        int prev_stars = 0;
        int repeatcnt = 0;
        bool converged = false;
        for (ndxc = 1; ndxc < pvecs.rows(); ++ndxc) {
            if (converged || !get_angs_c()) continue;

            Triangle abca(angs_c[0], angs_c[1], angs_c[2], tolerance, pairs, teststar, pvecs.row(ndxc).transpose());
            abca.side1.stars = ab.stars;
            abca.close_loops_abca();
            ab.append_iterations(abca.side1);

            std::vector<Triangle> triangles;
            triangles.push_back(abca);
            for (ndxd = 1; ndxd < pvecs.rows(); ++ndxd) {
                if (converged || !get_angs_d()) continue;

                Triangle abda(angs_d[0], angs_d[4], angs_d[3], tolerance, pairs, teststar, pvecs.row(ndxd).transpose());
                abda.side1.stars = ab.stars;
                abda.close_loops_abda(triangles);
                ab.append_iterations(abda.side1);
                triangles.push_back(abda);

                if (prev_stars == ab.stars.size()) ++repeatcnt; else repeatcnt = 0;
                if (repeatcnt > 3) converged = true;
                prev_stars = ab.stars.size();
                // std::cout << ndxb << ", " << ndxc << ", " << ndxd << ", " << ab.stars.size() << ", " << ab.has_teststar << ", " << repeatcnt << std::endl;
                if (ab.stars.size() == 1) break;
            }

            if (ab.stars.size() == 1) break;
        }

        if (ab.stars.size() == 1) {
            auto starsit = ab.stars.begin();
            return starsit->first;
        }
        abs.push_back(ab);
    }
    return -1;
}

bool id::star_identifier::get_angs_d() {
    if (ndxd == ndxb || ndxd == ndxc) return false;
    bool angsok = true;
    angs_d = angs_c;
    uvecd = pvecs.row(ndxd);
    angs_d.push_back(std::acos(uvecd.transpose() * uveca));
    angs_d.push_back(std::acos(uvecd.transpose() * uvecb));
    angs_d.push_back(std::acos(uvecd.transpose() * uvecc));
    if (angs_d[3] < min_ang) angsok = false; // da
    if (angs_d[4] < min_ang) angsok = false; // db
    if (angs_d[5] < min_ang) angsok = false; // dc
    if (std::abs(angs_d[4]-angs_d[3]) < min_ang) angsok = false; // db-da
    //if (std::abs(angs_d[4]-angs_d[0]) < min_ang) angsok = false; // db-ab
    //if (std::abs(angs_d[4]-angs_d[5]) < min_ang) angsok = false; // db-dc
    return angsok;
}

bool id::star_identifier::get_angs_c() {
    if (ndxc == ndxb) return false;
    bool angsok = true;
    angs_c.clear();
    uvecc = pvecs.row(ndxc);
    angs_c.push_back(std::acos(uveca.transpose() * uvecb));
    angs_c.push_back(std::acos(uvecb.transpose() * uvecc));
    angs_c.push_back(std::acos(uvecc.transpose() * uveca));
    min_ang = 3000.0 * stars::arcseconds_to_radians;
    if (angs_c[0] < min_ang) angsok = false; // ab
    if (angs_c[1] < min_ang) angsok = false; // bc
    if (angs_c[2] < min_ang) angsok = false; // ca
    if (std::abs(angs_c[0]-angs_c[1]) < min_ang) angsok = false; // ab-bc
    if (std::abs(angs_c[0]-angs_c[2]) < min_ang) angsok = false; // ab-ca
    if (std::abs(angs_c[1]-angs_c[2]) < min_ang) angsok = false; // bc-ca
    return angsok;
}







