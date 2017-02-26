#include "star_identifier.h"

rules::StarIdentifier::StarIdentifier(stars::Image& image,
                                      rules::PairsOverWholeSky& pairs,
                                      double tolrad) :
  all_pairs(pairs), image(image), tol_radius(tolrad) {
}

int rules::StarIdentifier::identifyCentralStar() {
  int teststar = 1;
  std::unordered_map<int, int> curstars;
  int num_stars = image.uvecs.n_rows;
  uveca = arma::trans(image.uvecs.row(0));

  for (int ndxb = 1; ndxb < num_stars; ++ndxb) { // star b /////////////////
    uvecb = arma::trans(image.uvecs.row(ndxb));
    double angab = std::acos(arma::dot(uveca, uvecb));
    TriangleSide abfirst(angab, tol_radius, all_pairs, teststar);
    int starccnt = 0;
    Triangle abca(teststar); // placeholder for focus on side ab

    for (int ndxc = 1; ndxc < num_stars; ++ndxc) { // star c //////////////
      if (ndxc == ndxb || skip_c(ndxc)) continue;
      if (starccnt == 0)
        abca.side1.stars = abfirst.stars;
      else
        abca.side1.refresh_pairs(abfirst);
      ++starccnt;
      if (starccnt > 3) continue; // early stop on star c
      rules::TriangleSide side2(angs_c[1], tol_radius, all_pairs, teststar);
      rules::TriangleSide side3(angs_c[2], tol_radius, all_pairs, teststar);
      abca.side2.stars = side2.stars;
      abca.side3.stars = side3.stars;
      abca.link_sides();
      TriangleSide cafirst = abca.side3;
      Triangle abda = abca;
      Triangle adca = abca;

      for (int ndxd = 1; ndxd < num_stars; ++ndxd) { // star d /////////////
        if (ndxd == ndxb || ndxd == ndxc || skip_d(ndxd)) continue;
        rules::TriangleSide bd(angs_d[4], tol_radius, all_pairs, teststar);
        rules::TriangleSide da(angs_d[3], tol_radius, all_pairs, teststar);
        abda.side1.refresh_pairs(abfirst);
        abda.side2.stars = bd.stars;
        abda.side3.stars = da.stars;
        abda.link_sides();

        rules::TriangleSide dc(angs_d[5], tol_radius, all_pairs, teststar);
        adca.side1.stars = da.stars; //abda.side3.stars;
        adca.side2.stars = dc.stars;
        adca.side3.refresh_pairs(cafirst);
        adca.link_sides();

        abca.update_side1(abda.side1);
        abca.update_side3(adca.side3);
        abca.link_sides();
        std::cout << abca.side1.log_star_count.size() << ' '
                  << abca.side1.stars.size() << ' '
                  << abca.side1.log_teststar.back() << std::endl;
      } // star d ///////////////////////////////////////////////////////////

      continue;
    } // star c ///////////////////////////////////////////////////////////////

    std::unordered_map<int, int> merged; // = ad.stars_in_three_sides(ab, ac);
    update_stars(curstars, merged);
  } // star b //////////////////////////////////////////////////////////////////

  std::map<int, int> starsa;
  std::multimap<int, int, std::greater<int>> starsb;
  for (auto it = curstars.begin(), end = curstars.end(); it != end; ++it) {
    starsa.emplace(it->first, it->second);
    starsb.emplace(it->second, it->first);
  }
  return -1;
}

bool rules::StarIdentifier::skip_c(int ndxc) {
  bool result = false;
  angs_c.clear();
  uvecc = arma::trans(image.uvecs.row(ndxc));
  angs_c.push_back(std::acos(arma::dot(uveca, uvecb)));
  angs_c.push_back(std::acos(arma::dot(uvecb, uvecc)));
  angs_c.push_back(std::acos(arma::dot(uvecc, uveca)));
  min_ang = 3000.0 * stars::arcseconds_to_radians;
  if (angs_c[0] < min_ang) result = true; // ab
  if (angs_c[1] < min_ang) result = result; // bc allow
  if (angs_c[2] < min_ang) result = true; // ca
  if (std::abs(angs_c[0]-angs_c[1]) < min_ang) result = true; // ab-bc
  if (std::abs(angs_c[0]-angs_c[2]) < min_ang) result = true; // ab-ca
  if (std::abs(angs_c[1]-angs_c[2]) < min_ang) result = true; // bc-ca
  return result;
}

bool rules::StarIdentifier::skip_d(int ndxd) {
  bool result = false;
  angs_d = angs_c;
  uvecd = arma::trans(image.uvecs.row(ndxd));
  angs_d.push_back(std::acos(arma::dot(uvecd, uveca)));
  angs_d.push_back(std::acos(arma::dot(uvecd, uvecb)));
  angs_d.push_back(std::acos(arma::dot(uvecd, uvecc)));
  if (angs_d[3] < min_ang) result = true; // da allow
  if (angs_d[4] < min_ang) result = true; // db
  if (angs_d[5] < min_ang) result = true; // dc
  if (std::abs(angs_d[4]-angs_d[3]) < min_ang) result = true; // db-da
  return result;
}

void rules::StarIdentifier::update_stars(std::unordered_map<int, int>& stars1, const std::unordered_map<int, int>& stars2){
  for (auto it2 = stars2.begin(), end = stars2.end(); it2 != end; ++it2) {
    auto it1 = stars1.find(it2->first);
    if (it1 != stars1.end()) {
      ++it1->second;
    } else {
      stars1.emplace(it2->first, 1);
    }
  }
}





