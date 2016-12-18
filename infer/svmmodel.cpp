#include "svmmodel.h"

//svm::Model::Model(stars::Training &trainingset) {
//    using namespace arma;

//    gamma = 1.0;
//    epsilon = 0.001;
//    Cval = 1.0;

//    xvecs = trainingset.examples;
//    yvec = trainingset.labels;
//    lval = yvec.n_rows;

//    biasval = 0.0;
//    alphavec.zeros(lval);
//    Kmat.zeros(lval,lval);
//    Qmat = Kmat;

//    for (uint i = 0; i < lval; ++i) {
//        for (uint j = i; j < lval; ++j) {

//            vec veci = trans(xvecs.row(i));
//            vec vecj = trans(xvecs.row(j));

//            Kmat(i,j) = Kernel(veci, vecj);
//            Qmat(i,j) = yvec(i) * yvec(j) * Kmat(i,j);

//            Kmat(j,i) = Kmat(i,j);
//            Qmat(j,i) = Qmat(i,j);
//        }
//    }

//}

double convnet::SvmModel::Kernel(arma::vec &veci, arma::vec &vecj) {
    return exp( -gamma * arma::dot( veci-vecj , veci-vecj ) ); // rbf kernel
}

double convnet::SvmModel::Predict(arma::vec &vecx) {

    double decisionval = biasval;
    for (uint i = 0; i < lval; ++i) {
            arma::vec veci = trans(xvecs.row(i));
            decisionval += yvec(i) * alphavec(i) * Kernel(veci, vecx);
    }

    return decisionval;
}

