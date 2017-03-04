#include "star_identifier.h"

rules::StarIdentifier::StarIdentifier(stars::Image& image,
                                      rules::PairsOverWholeSky& pairs,
                                      double tolrad) :
  all_pairs(pairs), image(image), tol_radius(tolrad) {
}

int rules::StarIdentifier::identifyCentralStar(int teststar = 1) {

  for (ndxb = 2;;) { // ndxb = 1; ndxb < image.uvecs.n_rows; ++ndxb) {

    uveca = arma::trans(image.uvecs.row(0));
    uvecb = arma::trans(image.uvecs.row(ndxb));
    TriangleSide abinit(std::acos(arma::dot(uveca, uvecb)), tol_radius, all_pairs, teststar);
    TriangleSide ab = abinit; // evolve ab over star c cycles

    for (ndxc = 1; ndxc < image.uvecs.n_rows; ++ndxc) {
      if (!get_angs_c()) continue;

      Triangle abca(angs_c[0], angs_c[1], angs_c[2], tol_radius, all_pairs, teststar);
      abca.link_side1_and_side3(1);
      ab.stars = abca.side1.stars;

      std::vector<Triangle> abdas;
      for (ndxd = 1; ndxd < image.uvecs.n_rows; ++ndxd) {
        if (!get_angs_d()) continue;

        Triangle abda = new_abda(abca);
        abda.side1.stars = ab.stars;
        abda.link_side1_and_side3(1);
        abdas.push_back(abda);
        ab.stars = abda.side1.stars;
      }

      continue;
    }
  }
  return -1;
}

void rules::StarIdentifier::msg_abca(Triangle &abca) {
  std::cout << ndxb << ' ' << ndxc << ' ' << ndxd << ' '
            << abca.side1.log_star_count.size() << ' '
            << abca.side1.stars.size() << ' '
            << abca.side1.log_teststar.back() << std::endl;
}

rules::Triangle rules::StarIdentifier::new_abda(Triangle &abca) {
  Triangle abda = abca;
  rules::TriangleSide bd(angs_d[4], tol_radius, all_pairs, teststar);
  rules::TriangleSide da(angs_d[3], tol_radius, all_pairs, teststar);
  abda.side2.stars = bd.stars;
  abda.side3.stars = da.stars;
  return abda;
}

rules::Triangle rules::StarIdentifier::new_adca(Triangle &abca) {
  Triangle adca = abca;
  rules::TriangleSide ad(angs_d[3], tol_radius, all_pairs, teststar);
  rules::TriangleSide dc(angs_d[5], tol_radius, all_pairs, teststar);
  adca.side1.stars = ad.stars; //abda.side3.stars;
  adca.side2.stars = dc.stars;
  return adca;
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
  return angsok;
}





