#include "gtest/gtest.h"


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    ::testing::GTEST_FLAG(filter) = "base_geometry.unitvector"
                                    ":base_geometry.rotation"
                                    ":base_sensor.endtoend";
    return RUN_ALL_TESTS();
}
