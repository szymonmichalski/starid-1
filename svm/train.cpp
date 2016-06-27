#include "train.h"
#include <cassert>

svm::Train::Train(svm::Model& model) {
    using namespace arma;
    epsilon = model.epsilon;
    lval = model.lval;
    Cval = model.Cval;
    bvec.ones(lval);
    pvec = -bvec;
    yvec = model.yvec;
    Kmat = model.Kmat;
    Qmat = model.Qmat;
    alphavec = model.alphavec;
    biasval = 0.0;
}

void svm::Train::MainLoop() {
    using namespace arma;
    vec alphavecprev;
    mat Qcols = zeros(lval,2);

    gradient = (Qmat * alphavec) + pvec;
    for (uint k = 0; k < 1000000; ++k) {
        if (!WorkingSet()) break;
        alphavecprev = alphavec;
        SubProblem();
        Qcols.col(0) = Qmat.col(wsi);
        Qcols.col(1) = Qmat.col(wsj);
        gradient = gradient + (Qcols * (alphavec - alphavecprev));
    }

    for (uint i = 0; i < lval; ++i) {
        if (alphavec(i) > 0.0 && alphavec(i) < Cval) {
            biasval = yvec(i) * gradient(i);
            break;
        }
    }
}

void::svm::Train::SubProblem() {
    using namespace arma;
    double aij = Kmat(wsi,wsi) + Kmat(wsj,wsj) - 2*Kmat(wsi,wsj);
    if (aij <= 0.0) aij = 1.0e-9;
    double bij = -(yvec(wsi) * gradient(wsi)) + (yvec(wsj) * gradient(wsj));
    alphavec(wsi) = alphavec(wsi) + (yvec(wsi) * bij / aij);
    alphavec(wsj) = alphavec(wsj) - (yvec(wsj) * bij / aij);
    if (alphavec(wsi) < 0.0) alphavec(wsi) = 0.0;
    if (alphavec(wsj) < 0.0) alphavec(wsj) = 0.0;
    if (alphavec(wsi) > Cval) alphavec(wsi) = Cval;
    if (alphavec(wsj) > Cval) alphavec(wsj) = Cval;
}

bool svm::Train::WorkingSet() {
    using namespace arma;
    double malpha = -1.0e9;
    double Malpha = 1.0e9;
    vec upflags = zeros(lval);
    vec lowflags = zeros(lval);
    for (uint i = 0; i < lval; ++i) {
        assert (yvec(i) == 1.0 || yvec(i) == -1.0);
        if (yvec(i) == 1.0) {
            if (alphavec(i) < Cval) upflags(i) = 1.0;
            if (alphavec(i) > 0.0) lowflags(i) = 1.0;
        }
        else {
            if (alphavec(i) < Cval) lowflags(i) = 1.0;
            if (alphavec(i) > 0.0) upflags(i) = 1.0;
        }
        double grad = -yvec(i) * gradient(i);
        if (upflags(i) == 1.0) {
            if (grad > malpha) {
                malpha = grad;
                wsi = i;
            }
        }
        if (lowflags(i) == 1.0) {
            if (grad < Malpha) {
                Malpha = grad;
            }
        }
    }
    double curmin = 1.0e9;
    for (uint j = 0; j < lval; ++j) { // wsj
        if (!(-gradient(j) < -gradient(wsi))) continue;
        if (lowflags(j) == 1.0) {
            double ait = Kmat(wsi,wsi) + Kmat(j,j) - 2*Kmat(wsi,j);
            if (ait <= 0.0) ait = 1.0e-9;
            double bit = -gradient(wsi) + gradient(j);
            if (-bit*bit/ait < curmin) {
                curmin = -bit*bit/ait;
                wsj = j;
            }
        }
    }
    if (malpha - Malpha <= epsilon) return false; // stopping criteria
    return true;
}


