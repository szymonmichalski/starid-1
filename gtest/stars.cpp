#include "pointing.h"

#include "gtest/gtest.h"
#include <armadillo>

TEST(stars, test1) {
    double ra = 0.0 * arma::datum::pi / 180.0; // cass
    double dec = 60.0 * arma::datum::pi / 180.0; // cass

    stars::Pointing pointing(ra, dec, 0.0);
    EXPECT_EQ(norm(pointing.uv), 1.0);
}

TEST(stars, test2) {
double ra = 0.0 * arma::datum::pi / 180.0; // cass
double dec = 60.0 * arma::datum::pi / 180.0; // cass

    stars::Pointing pointing(ra, dec, 0.0);
    EXPECT_EQ(det(pointing.RotationMatrix()), 1.0);
}

