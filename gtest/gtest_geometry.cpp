#include "gtest/gtest.h"
#include "../base/geometry.h"

TEST(Geometry, Basic) {
    constexpr double ra = 0.0*datum::pi/180.0; // cass
    constexpr double dec = 60.0*datum::pi/180.0; // cass

    geometry::UnitVector uv;
    EXPECT_EQ(norm(uv.uv), 1);
    geometry::RotationMatrix rm;
    EXPECT_EQ(det(rm.rm), 1);
    geometry::Quaternion q;
    EXPECT_EQ(norm(q.q), 1);


    geometry::UnitVector uv2(ra,dec);
    geometry::Quaternion q2(uv2,0.0);
    EXPECT_EQ(norm(q2.q), 1);
}
