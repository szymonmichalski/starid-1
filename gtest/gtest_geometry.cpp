#include "gtest/gtest.h"
#include "../base/geometry.h"

TEST(Geometry, Basic) {
    constexpr double ra = 0.0*datum::pi/180.0; // cass
    constexpr double dec = 60.0*datum::pi/180.0; // cass

    geometry::Pointing pointing(ra, dec, 0.0);
    EXPECT_EQ(norm(pointing.uv), 1.0);
    EXPECT_EQ(det(pointing.RotationMatrix()), 1.0);
}
