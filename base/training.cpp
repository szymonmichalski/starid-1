#include "training.h"

base::Training::Training(uint cnt_inclass, uint cnt_outofclass) {
    TrainingSet trainingset;
    trainingset.cntinclass = cnt_inclass;
    trainingset.cntoutofclass = cnt_outofclass;
}

void base::Training::Status() {

}
