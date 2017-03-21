#include "star_identifier.h"

rules::StarIdentifier::StarIdentifier(stars::Image& image,
                                      rules::PairsOverWholeSky& pairs,
                                      double tolrad) :
  pairs(pairs), image(image), tolerance(tolrad) {
}

int rules::StarIdentifier::identifyCentralStar(int teststar = 1) {

  std::vector<TriangleSide> abs;
  for (ndxb = 1; ndxb < image.uvecs.n_rows; ++ndxb) {

    uveca = arma::trans(image.uvecs.row(0));
    uvecb = arma::trans(image.uvecs.row(ndxb));
    TriangleSide ab(std::acos(arma::dot(uveca, uvecb)), tolerance, pairs, teststar);

    int prev_stars = 0;
    int repeatcnt = 0;
    bool converged = false;
    for (ndxc = 1; ndxc < image.uvecs.n_rows; ++ndxc) {
      if (converged || !get_angs_c()) continue;

      Triangle abca(angs_c[0], angs_c[1], angs_c[2], tolerance, pairs, teststar, arma::trans(image.uvecs.row(ndxc)));
      abca.side1.stars = ab.stars;
      abca.close_loops_abca();
      ab.append_iterations(abca.side1);

      std::vector<Triangle> abdas;
      for (ndxd = 1; ndxd < image.uvecs.n_rows; ++ndxd) {
        if (converged || !get_angs_d()) continue;

        Triangle abda(angs_d[0], angs_d[4], angs_d[3], tolerance, pairs, teststar, arma::trans(image.uvecs.row(ndxd)));
        abda.side1.stars = ab.stars;
        abda.close_loops_abda(abca, abdas);
        ab.append_iterations(abda.side1);
        abdas.push_back(abda);

        if (prev_stars == ab.stars.size()) ++repeatcnt; else repeatcnt = 0;
        if (repeatcnt > 3) converged = true;
        prev_stars = ab.stars.size();
        std::cout << ndxb << ", " << ndxc << ", " << ndxd << ", "
                  << ab.stars.size() << ", " << ab.has_teststar << ", "
                  << repeatcnt << std::endl;
      }

      //std::cout << ndxb << ' ' << ndxc << std::endl;
    }

    abs.push_back(ab);
    continue;
  }
  return -1;
}

bool rules::StarIdentifier::get_angs_d() {
  if (ndxd == ndxb || ndxd == ndxc) return false;
  bool angsok = true;
  angs_d = angs_c;
  uvecd = arma::trans(image.uvecs.row(ndxd));
  angs_d.push_back(std::acos(arma::dot(uvecd, uveca)));
  angs_d.push_back(std::acos(arma::dot(uvecd, uvecb)));
  angs_d.push_back(std::acos(arma::dot(uvecd, uvecc)));
  if (angs_d[3] < min_ang) angsok = false; // da
  if (angs_d[4] < min_ang) angsok = false; // db
  if (angs_d[5] < min_ang) angsok = false; // dc
  if (std::abs(angs_d[4]-angs_d[3]) < min_ang) angsok = false; // db-da
  //if (std::abs(angs_d[4]-angs_d[0]) < min_ang) angsok = false; // db-ab
  //if (std::abs(angs_d[4]-angs_d[5]) < min_ang) angsok = false; // db-dc
  return angsok;
}

bool rules::StarIdentifier::get_angs_c() {
  if (ndxc == ndxb) return false;
  bool angsok = true;
  angs_c.clear();
  uvecc = arma::trans(image.uvecs.row(ndxc));
  angs_c.push_back(std::acos(arma::dot(uveca, uvecb)));
  angs_c.push_back(std::acos(arma::dot(uvecb, uvecc)));
  angs_c.push_back(std::acos(arma::dot(uvecc, uveca)));
  min_ang = 3000.0 * stars::arcseconds_to_radians;
  if (angs_c[0] < min_ang) angsok = false; // ab
  if (angs_c[1] < min_ang) angsok = false; // bc
  if (angs_c[2] < min_ang) angsok = false; // ca
  if (std::abs(angs_c[0]-angs_c[1]) < min_ang) angsok = false; // ab-bc
  if (std::abs(angs_c[0]-angs_c[2]) < min_ang) angsok = false; // ab-ca
  if (std::abs(angs_c[1]-angs_c[2]) < min_ang) angsok = false; // bc-ca
  return angsok;
}







