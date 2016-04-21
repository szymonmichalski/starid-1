#include "triplets.h"

pairs::Triplets::Triplets() {}
pairs::Triplets::Triplets(base::Obs& obs)
    : n(obs.uv.n_rows), curtriplet(0)
{
    mata.zeros(n,3);
    matb.zeros(n,3);
    matc.zeros(n,3);
    uint cnt {0};
    uint i, j, k, dj, dk;
    for (dj = 1; dj <= n-2; ++dj) {
        for (dk = 1; dk <= n-dj-1; ++dk) {
            for (i = 1; i <= n-dj-dk; ++i) {
                j = i + dj;
                k = j + dk;
                // current triplet is stars i, j, and k
                mata.row(cnt) = obs.uv.row(i-1);
                matb.row(cnt) = obs.uv.row(j-1);
                matc.row(cnt) = obs.uv.row(k-1);
                ++cnt;
            }
        }
    }
}

arma::mat pairs::Triplets::getTriplet() {
    arma::mat triplet;
    triplet.zeros(3,3);
    if (curtriplet >= mata.n_rows) {
        return triplet;
    }
    triplet.row(0) = mata.row(curtriplet);
    triplet.row(1) = matb.row(curtriplet);
    triplet.row(2) = matc.row(curtriplet);
    ++curtriplet;
    return triplet;
}
