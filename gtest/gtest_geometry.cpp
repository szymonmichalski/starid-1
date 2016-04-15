#include "gtest/gtest.h"
#include "../base/geometry.h"

TEST(Geometry, Basic) {
    geometry::Quaternion q;
    EXPECT_LE(norm(q.q), 1);
}
