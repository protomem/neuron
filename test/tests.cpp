#include <gtest/gtest.h>

#include "neuron.hpp"

using namespace std;

TEST(Neuron, Neuron)
{
    neuron::Neuron n;
    ASSERT_TRUE(1 == 1);
}

TEST(Neuron, Neuron2)
{
    neuron::Neuron n;
    ASSERT_TRUE(1 == 2);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
