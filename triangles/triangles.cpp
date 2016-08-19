#include "triangles.h"

triangles::Triangles::Triangles(stars::Sensor &sensor, uint triplets_max)
    : n(sensor.stars.starsvec.size()), curtriplet(0)
{
    mata.zeros(triplets_max,3);
    matb.zeros(triplets_max,3);
    matc.zeros(triplets_max,3);
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
                if (cnt == triplets_max-1) break;
            }
            if (cnt == triplets_max-1) break;
        }
        if (cnt == triplets_max-1) break;
    }
    if (cnt < triplets_max-1) {
        mata.shed_rows(cnt,triplets_max-1);
        matb.shed_rows(cnt,triplets_max-1);
        matc.shed_rows(cnt,triplets_max-1);
    }
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
