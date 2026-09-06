#include <gtest/gtest.h>

#include "../include/neuron.hpp"

TEST(NeuronVersionTest, ValidateVersion)
{
    const auto v = neuron::version();
    EXPECT_FALSE(v.empty());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
