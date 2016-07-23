#include "gtest/gtest.h"
#include <armadillo>

int main(int argc, char **argv)
{
    arma::arma_rng::set_seed_random();

    ::testing::InitGoogleTest(&argc, argv);

//    ::testing::GTEST_FLAG(filter) = "stars.pointing1"
//                                    ":stars.pointing2";

    return RUN_ALL_TESTS();
}
