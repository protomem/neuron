#include <gtest/gtest.h>
#include <iostream>

#include "IrisTestSuite.hpp"

TEST(IrisTestSuite, Main)
{
    IrisTestSuite testSuite("../../../examples/iris/dataset.csv");
    auto result = testSuite.Classify();

    EXPECT_TRUE(result.IsEmpty())
        << result.correct << " correct of "
        << result.trails << " = "
        << (result.percentage * 100) << "%"
        << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
