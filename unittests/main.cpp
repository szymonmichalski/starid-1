#include "gtest/gtest.h"


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    ::testing::GTEST_FLAG(filter) = "base_pointing.unitvector"
                                    ":base_pointing.rotation"
                                    ":base_main.endtoend"
                                    ":ptq_main.endtoend";
    return RUN_ALL_TESTS();
}
