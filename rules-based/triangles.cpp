#include "triangles.h"
#include "stopwatch.h"
#include <map>

rules::Triangles::Triangles(stars::Sensor& sensor,
                            rules::PairsOverWholeSky& pairs,
                            double triangle_tol,
                            int max_triangles) :
    pairsOverWholeSky(pairs),
    sensor(sensor),
    triangle_tol(triangle_tol),
    max_triangles(max_triangles),
    num_stars(sensor.l1_uvec.n_rows),
    cur_triangle(0)
{}

int rules::Triangles::identifyCentralStar() {
    arma::mat mata;
    arma::mat matb;
    arma::mat matc;
    mata.zeros(max_triangles,3);
    matb.zeros(max_triangles,3);
    matc.zeros(max_triangles,3);
    cur_triangle = 0;
    uint i, j, k, dj, dk;
    for (dj = 1; dj <= num_stars-2; ++dj) {
        for (dk = 1; dk <= num_stars-dj-1; ++dk) {
            for (i = 1; i <= num_stars-dj-dk; ++i) {
                j = i + dj;
                k = j + dk;
                // stara near center of field of view
                if (sensor.l1_hv(i-1,0) > 100 * arma::datum::pi / 648e3
                    || sensor.l1_hv(i-1,1) > 100 * arma::datum::pi / 648e3) continue;
                mata.row(cur_triangle) = sensor.l1_uvec.row(i-1);
                matb.row(cur_triangle) = sensor.l1_uvec.row(j-1);
                matc.row(cur_triangle) = sensor.l1_uvec.row(k-1);
                ++cur_triangle;
                if (cur_triangle == max_triangles-1) break;
            }
            if (cur_triangle == max_triangles-1) break;
        }
        if (cur_triangle == max_triangles-1) break;
    }
    if (cur_triangle < max_triangles-1) {
        mata.shed_rows(cur_triangle,max_triangles-1);
        matb.shed_rows(cur_triangle,max_triangles-1);
        matc.shed_rows(cur_triangle,max_triangles-1);
    }
    std::vector<int> staraCandNdxs;
    for (uint i = 0; i < mata.n_rows; ++i) {
        rules::Triangle triangle;
        triangle.uva = arma::trans(mata.row(i));
        triangle.uvb = arma::trans(matb.row(i));
        triangle.uvc = arma::trans(matc.row(i));
        triangle.angab = acos(arma::dot(triangle.uva, triangle.uvb));
        triangle.angac = acos(arma::dot(triangle.uva, triangle.uvc));
        triangle.angbc = acos(arma::dot(triangle.uvb, triangle.uvc));
        // triangle sides are too similar
        if (std::abs(triangle.angab - triangle.angac) < triangle_tol
            || std::abs(triangle.angab - triangle.angbc) < triangle_tol
            || std::abs(triangle.angac - triangle.angbc) < triangle_tol) continue;
        std::vector<int> l1ab = pairsOverWholeSky.starsFromPairs(triangle.angab, 0.05 * triangle_tol);
        std::vector<int> l1ac = pairsOverWholeSky.starsFromPairs(triangle.angac, 0.05 * triangle_tol);
        std::vector<int> l1bc = pairsOverWholeSky.starsFromPairs(triangle.angbc, 0.05 * triangle_tol);
        std::vector<int> l2abac;
        std::vector<int> l2babc;
        std::vector<int> l2cacb;
        std::set_intersection(l1ab.begin(), l1ab.end(), l1ac.begin(), l1ac.end(), back_inserter(l2abac));
        std::set_intersection(l1ab.begin(), l1ab.end(), l1bc.begin(), l1bc.end(), back_inserter(l2babc));
        std::set_intersection(l1ac.begin(), l1ac.end(), l1bc.begin(), l1bc.end(), back_inserter(l2cacb));
        for (auto ndx : l2abac) staraCandNdxs.push_back(ndx);
    }
    int max = 0;
    int most_common = -1;
    std::map<int,int> m;
    for (auto it = staraCandNdxs.begin(); it != staraCandNdxs.end(); ++it) {
      m[*it]++;
      if (m[*it] > max) {
        max = m[*it];
        most_common = *it;
      }
    }
    return most_common;
}


