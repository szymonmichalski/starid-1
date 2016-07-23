#include "triplets.h"

pairs::Triplets::Triplets() {}
pairs::Triplets::Triplets(stars::L1& obs, uint nlimit)
    : n(obs.uv.n_rows), curtriplet(0)
{
    mata.zeros(nlimit,3);
    matb.zeros(nlimit,3);
    matc.zeros(nlimit,3);
    uint cnt {0};
    uint i, j, k, dj, dk;
    for (dj = 1; dj <= n-2; ++dj) {
        for (dk = 1; dk <= n-dj-1; ++dk) {
            for (i = 1; i <= n-dj-dk; ++i) {
                j = i + dj;
                k = j + dk;
                mata.row(cnt) = obs.uv.row(i-1);
                matb.row(cnt) = obs.uv.row(j-1);
                matc.row(cnt) = obs.uv.row(k-1);
                ++cnt;
                if (cnt == nlimit-1) break;
            }
            if (cnt == nlimit-1) break;
        }
        if (cnt == nlimit-1) break;
    }
    if (cnt < nlimit-1) {
        mata.shed_rows(cnt,nlimit-1);
        matb.shed_rows(cnt,nlimit-1);
        matc.shed_rows(cnt,nlimit-1);
    }
}

pairs::Triplet pairs::Triplets::GetTriplet(double tol) {
    pairs::Triplet triplet;
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

bool pairs::Triplets::IsMoreTriplets() {
    if (curtriplet >= mata.n_rows) return false;
    return true;
}
