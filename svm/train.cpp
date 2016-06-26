#include "train.h"
#include <cassert>

svm::Train::Train(svm::Model& model) {
    epsilon = model.epsilon;
    lval = model.lval;
    Cval = model.Cval;
    bvec.ones(lval);
    pvec = -bvec;
    yvec = model.yvec;
    Qmat = model.Qmat;
    alphavec = model.alphavec;
    gradientvec = Qmat * alphavec + pvec;
}

bool svm::Train::StoppingCriteria() {
    gradientvec = Qmat * alphavec + pvec;
    double malpha = -1.0e12;
    double Malpha = 1.0e12;
    bool mflag {false};
    bool Mflag {false};
    for (uint i = 0; i < lval; ++i) {
        assert (yvec(i) == 1.0 || yvec(i) == -1.0);
        if (yvec(i) == 1.0) {
            if (alphavec(i) < Cval) mflag = true;
            if (alphavec(i) > 0.0) Mflag = true;
        }
        else {
            if (alphavec(i) < Cval) Mflag = true;
            if (alphavec(i) > 0.0) mflag = true;
        }
        if (mflag) {
            if ( (-yvec(i) * gradientvec(i)) > malpha ) {
                malpha = -yvec(i) * gradientvec(i);
            }
        }
        if (Mflag) {
            if ( (-yvec(i) * gradientvec(i)) < Malpha ) {
                Malpha = -yvec(i) * gradientvec(i);
            }
        }
    }
    if (malpha - Malpha <= epsilon) return true;
    return false;
}

void svm::Train::SelectWorkingSet(uint& wsndx1, uint& wsndx2) {

}

