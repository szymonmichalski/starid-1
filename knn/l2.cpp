#include "l2.h"

uint knn::L2::Classify(arma::vec& fv) {
    using namespace arma;
    uint catndx = 0;
    rowvec distances = trans(fv) * l2a;
    uvec ndxs = sort_index(trans(distances), "descend");
    catndx = ndxs(0);
    return catndx;
}

knn::L2::L2(base::Catalog &catalog, base::Sensor &sensor) {
    l2a.zeros(1e2, catalog.stars.size());
    l2b.zeros(1e4, catalog.stars.size());
    for (uint i = 0; i <= catalog.stars.size()-1; ++i) {
        base::Pointing p(catalog.stars[i].ra, catalog.stars[i].dec, 0.0);
        sensor.L1a(catalog, p);
        l2a.col(i) = sensor.l2.fv1;
        l2b.col(i) = sensor.l2.fv2;
    }
}

void knn::L2::StatusFeatures() {
    using namespace arma;
    rowvec nfeaturesa = sum(l2a);
    rowvec nfeaturesb = sum(l2b);
    std::cout << hist(nfeaturesa, linspace<vec>(0,60,10)) << "\n";
    std::cout << hist(nfeaturesb, linspace<vec>(0,60,10)) << "\n";
}

void knn::L2::StatusOrthogonality() {
    using namespace arma;
    mat dota = trans(normalise(l2a)) * normalise(l2a);
    mat dotb = trans(normalise(l2b)) * normalise(l2b);
    vec tmpa = vectorise(dota);
    vec tmpb = vectorise(dotb);
    uvec hista = hist(tmpa, linspace<vec>(0,1,10))/2;
    uvec histb = hist(tmpb, linspace<vec>(0,1,10))/2;
    hista(9) = hista(9) - 4439;
    histb(9) = histb(9) - 4439;
    std::cout << trans(hista) << "\n";
    std::cout << trans(histb) << "\n";
}

