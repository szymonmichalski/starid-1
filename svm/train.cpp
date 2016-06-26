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
    gradient = (Qmat * alphavec) + pvec;

    Qbb = zeros(2,2);
    alphab = zeros(2);
    gradb = zeros(2);
    Qbcols = zeros(lval,2);
    eq20 = zeros(2);
}

void svm::Train::MainLoop() {
    using namespace arma;
    uint loopcnt = 0;
    while (loopcnt < 1e6) {
        ++loopcnt;
        alphavecprev = alphavec;
        if (!WorkingSet()) break;
        UpdateEq20();
        SubProblem();
        UpdateGradient();
    }
}

void::svm::Train::UpdateEq20() {
    using namespace arma;
    gradb(0) = gradient(wsi);
    gradb(1) = gradient(wsj);
    Qbb(0,0) = Qmat(wsi,wsi);
    Qbb(0,1) = Qmat(wsi,wsj);
    Qbb(1,0) = Qmat(wsj,wsi);
    Qbb(1,1) = Qmat(wsj,wsj);
    alphab(0) = alphavec(wsi);
    alphab(1) = alphavec(wsj);
    eq20 = gradb + (Qbb * alphab);
}

void::svm::Train::UpdateGradient() {
    using namespace arma;

}

void::svm::Train::SubProblem() {
    using namespace arma;

}

bool svm::Train::WorkingSet() {
    using namespace arma;
//    gradientvec = Qmat * alphavec + pvec;
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
        if (upflags(i) == 1.0) {
            if (-yvec(i) * gradient(i) > malpha) {
                malpha = -yvec(i) * gradient(i);
                wsi = i;
            }
        }
        if (lowflags(i) == 1.0) {
            if (-yvec(i) * gradient(i) < Malpha) Malpha = -yvec(i) * gradient(i);
        }
    }
    double curmin = 1.0e9;
    for (uint j = 0; j < lval; ++j) { // wsj
        if (!(-gradient(j) < -gradient(wsi))) continue;
        if (lowflags(j) == 1.0) {
            double ait = Kmat(wsi,wsi) * Kmat(j,j) - 2*Kmat(wsi,j);
            if (ait <= 0.0 ) ait = 1.0e-9;
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


