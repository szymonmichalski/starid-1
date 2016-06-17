#include "gtest/gtest.h"
#include <armadillo>

int main(int argc, char **argv)
{
    arma::arma_rng::set_seed_random();

    ::testing::InitGoogleTest(&argc, argv);

//    ::testing::GTEST_FLAG(filter) = "knn_l2.l2";
//    ::testing::GTEST_FLAG(filter) = "base_pointing.unitvector"
//                                    ":base_pointing.rotation"
//                                    ":base_main.endtoend"
//                                    ":ptq_main.endtoend";

    return RUN_ALL_TESTS();
}
