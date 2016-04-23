#include "triplets.h"

pairs::Triplets::Triplets() {}
pairs::Triplets::Triplets(base::Obs& obs, uint ntrip)
    : n(obs.uv.n_rows), curtriplet(0)
{
    mata.zeros(ntrip,3);
    matb.zeros(ntrip,3);
    matc.zeros(ntrip,3);
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
                if (cnt == ntrip-1) break;
            }
            if (cnt == ntrip-1) break;
        }
        if (cnt == ntrip-1) break;
    }
    if (cnt < ntrip-1) {
        mata.shed_rows(cnt,ntrip-1);
        matb.shed_rows(cnt,ntrip-1);
        matc.shed_rows(cnt,ntrip-1);
    }
}

pairs::Triplet pairs::Triplets::GetTriplet() {
    pairs::Triplet triplet;
    triplet.uva = arma::trans(mata.row(curtriplet));
    triplet.uvb = arma::trans(matb.row(curtriplet));
    triplet.uvc = arma::trans(matc.row(curtriplet));
    triplet.ang_ab = abs(acos(arma::dot(triplet.uva,triplet.uvb)));
    triplet.ang_ac = abs(acos(arma::dot(triplet.uva,triplet.uvc)));
    triplet.ang_bc = abs(acos(arma::dot(triplet.uvb,triplet.uvc)));
    ++curtriplet;
    return triplet;
}

bool pairs::Triplets::IsMoreTriplets() {
    if (curtriplet >= mata.n_rows) return false;
    return true;
}
