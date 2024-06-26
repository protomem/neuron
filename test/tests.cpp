#include <gtest/gtest.h>

#include "neuron.hpp"

using namespace std;
using namespace neuron;

TEST(math, dotProduct)
{
    ASSERT_EQ(math::dotProduct({ 1.0, 2.0, 3.0 }, { 1.0, 2.0, 3.0 }), 14.0);
    ASSERT_EQ(math::dotProduct({ 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }), 32.0);
}

TEST(math, sigmoid)
{
    ASSERT_NEAR(math::sigmoid(0.0), 0.5, 0.001);
    ASSERT_NEAR(math::sigmoid(1.0), 0.7310585786300049, 0.001);
    ASSERT_NEAR(math::sigmoid(-1.0), 0.2689414213699951, 0.001);
}

TEST(math, derivativeSigmoid)
{
    ASSERT_NEAR(math::derivativeSigmoid(0.0), 0.25, 0.001);
    ASSERT_NEAR(math::derivativeSigmoid(1.0), 0.19661193324148185, 0.001);
    ASSERT_NEAR(math::derivativeSigmoid(-1.0), 0.19661193324148185, 0.001);
}

TEST(Neuron, forward)
{
    Neuron n({ 0.1, 0.2, 0.3 }, 0.0, math::sigmoid, math::derivativeSigmoid);
    ASSERT_NEAR(n.forward({ 1.0, 2.0, 3.0 }), 0.80218388855858169, 0.001);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
