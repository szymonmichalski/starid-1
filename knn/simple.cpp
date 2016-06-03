#include "simple.h"

uint knn::Simple::Classify(arma::vec& fv) {
    using namespace arma;
    uint catndx = 0;
    rowvec distances = trans(fv) * l2a;
    uvec ndxs = sort_index(trans(distances), "descend");
    catndx = ndxs(0);
    return catndx;
}

knn::Simple::Simple(base::Catalog &catalog, base::Sensor &sensor) {
    l2a.zeros(1e2, catalog.stars.size());
    for (uint i = 0; i <= catalog.stars.size()-1; ++i) {
        base::Pointing p(catalog.stars[i].ra, catalog.stars[i].dec, 0.0);
        sensor.L1a(catalog, p);
        sensor.L2a();
        l2a.col(i) = sensor.l2a.fv();
    }
}

void knn::Simple::StatusFeatures() {
    using namespace arma;
    rowvec nfeaturesa = sum(l2a);
    std::cout << hist(nfeaturesa, linspace<vec>(0,60,10)) << "\n";
}

void knn::Simple::StatusOrthogonality() {
    using namespace arma;
    mat dota = trans(normalise(l2a)) * normalise(l2a);
    vec tmpa = vectorise(dota);
    uvec hista = hist(tmpa, linspace<vec>(0,1,10))/2;
    hista(9) = hista(9) - 4439;
    std::cout << trans(hista) << "\n";
}

