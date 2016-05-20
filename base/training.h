#ifndef TRAINING_H
#define TRAINING_H

#include <armadillo>

namespace base {

struct TrainingSet {
    arma::mat examples; // n x l matrix of n dimensional feature vectors
    arma::vec labels; // l x 1 vector of class labels -1 (outofclass) or 1 (inclass)
    uint cntinclass;
    uint cntoutofclass;
};

class Training {
public:
    Training(uint cnt_inclass, uint cnt_outofclass);
    void Status();
private:
};

}

#endif // TRAINING_H
