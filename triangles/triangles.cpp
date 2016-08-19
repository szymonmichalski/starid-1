#include "triangles.h"

uint triangles::Triangles::MatchTriangles() {

    while (IsMoreTriplets()) {

        GetTriplet(triangle_tol);

        if (is_triplet_good) {

            std::vector<int> l1ab = pairs.Candidates(triangle.angab, 0.05 * triangle_tol);
            std::vector<int> l1ac = pairs.Candidates(triangle.angac, 0.05 * triangle_tol);
            std::vector<int> l1bc = pairs.Candidates(triangle.angbc, 0.05 * triangle_tol);
            std::vector<int> l2abac;
            std::vector<int> l2babc;
            std::vector<int> l2cacb;
            std::set_intersection(l1ab.begin(), l1ab.end(),
                                  l1ac.begin(), l1ac.end(),
                                  back_inserter(l2abac));
            std::set_intersection(l1ab.begin(), l1ab.end(),
                                  l1bc.begin(), l1bc.end(),
                                  back_inserter(l2babc));
            std::set_intersection(l1ac.begin(), l1ac.end(),
                                  l1bc.begin(), l1bc.end(),
                                  back_inserter(l2cacb));

        }
    }

}

void triangles::Triangles::StarPairsInImage(stars::Sensor &sensor) {
    mata.zeros(max_triangles,3);
    matb.zeros(max_triangles,3);
    matc.zeros(max_triangles,3);

    uint cnt {0};
    uint i, j, k, dj, dk;
    for (dj = 1; dj <= n-2; ++dj) {
        for (dk = 1; dk <= n-dj-1; ++dk) {
            for (i = 1; i <= n-dj-dk; ++i) {
                j = i + dj;
                k = j + dk;
                mata.row(cnt) = sensor.l1_uvec.row(i-1);
                matb.row(cnt) = sensor.l1_uvec.row(j-1);
                matc.row(cnt) = sensor.l1_uvec.row(k-1);
                ++cnt;
                if (cnt == max_triangles-1) break;
            }
            if (cnt == max_triangles-1) break;
        }
        if (cnt == max_triangles-1) break;
    }

    if (cnt < max_triangles-1) {
        mata.shed_rows(cnt,max_triangles-1);
        matb.shed_rows(cnt,max_triangles-1);
        matc.shed_rows(cnt,max_triangles-1);
    }
}

triangles::Triangles::Triangles(stars::Sensor &sensor, double triangle_tol, uint max_triangles)
    : n(sensor.stars.starsvec.size()),
      curtriplet(0),
      triangle_tol(triangle_tol),
      max_triangles(max_triangles)
{
    pairs.Init(sensor);
}

triangles::Triangle triangles::Triangles::GetTriplet(double tol) {
    triangles::Triangle triplet;
    triplet.uva = arma::trans(mata.row(curtriplet));
    triplet.uvb = arma::trans(matb.row(curtriplet));
    triplet.uvc = arma::trans(matc.row(curtriplet));
    triplet.angab = acos(arma::dot(triplet.uva, triplet.uvb));
    triplet.angac = acos(arma::dot(triplet.uva, triplet.uvc));
    triplet.angbc = acos(arma::dot(triplet.uvb, triplet.uvc));
    ++curtriplet;
    is_triplet_good = true;
//    std::cout << triplet.angab - triplet.angac << " " << tol << "\n";
    if (std::abs(triplet.angab - triplet.angac) < tol) is_triplet_good = false;
    if (std::abs(triplet.angab - triplet.angbc) < tol) is_triplet_good = false;
    if (std::abs(triplet.angac - triplet.angbc) < tol) is_triplet_good = false;
    return triplet;
}

bool triangles::Triangles::IsMoreTriplets() {
    if (curtriplet >= mata.n_rows) return false;
    return true;
}
