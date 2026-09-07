#include <gtest/gtest.h>

#include "neuron.hpp"
#include "neuron/Layer.hpp"
#include "neuron/Neuron.hpp"
#include "neuron/math.hpp"

TEST(NeuronVersionTest, ValidateVersion)
{
    const auto v = neuron::version();
    EXPECT_FALSE(v.empty());
}

TEST(NeuronTest, ForwardWithKnownWeights)
{
    using namespace neuron;

    std::vector<double> weights = { 1.0, 2.0, -1.0 };
    Neuron n(weights, /*learningRate*/ 0.1, math::sigmoid, math::sigmoid_derivative);

    std::vector<double> input = { 2.0, 0.5, 1.0 };
    // dot = 2*1 + 0.5*2 + 1*(-1) = 2 + 1 - 1 = 2
    double out = n.Forward(input);

    EXPECT_DOUBLE_EQ(out, math::sigmoid(2.0));
}

TEST(LayerTest, ForwardOutputLayer)
{
    using namespace neuron;

    auto prev = std::shared_ptr<Layer>(nullptr);
    Layer layer(prev, /*numNeurons*/ 2, /*learningRate*/ 0.1, math::sigmoid,
        math::sigmoid_derivative);

    std::vector<double> input = { 0.2, 0.8 };
    auto output = layer.Forward(input);

    ASSERT_EQ(output.size(), 2u);
}

TEST(LayerTest, CalcDeltaOutputLayer)
{
    using namespace neuron;

    auto prev = std::shared_ptr<Layer>(nullptr);
    Layer layer(prev, /*numNeurons*/ 2, /*learningRate*/ 0.1, math::sigmoid,
        math::sigmoid_derivative);

    std::vector<double> input = { 0.2, 0.8 };
    auto output = layer.Forward(input);

    std::vector<double> expected = { 0.0, 1.0 };
    layer.CalcDelta(expected);

    // Проверяем, что дельты установлены (не NaN и не бесконечность)
    for (const auto& n : layer._neurons) {
        EXPECT_TRUE(std::isfinite(n._delta));
    }
}

TEST(LayerTest, CalcDeltaHiddenLayer)
{
    using namespace neuron;

    // Входной слой
    auto inputLayer = std::make_shared<Layer>(nullptr, 2, 0.1, nullptr, nullptr);

    // Скрытый слой с активацией
    Layer hidden(inputLayer, 2, 0.1, math::sigmoid, math::sigmoid_derivative);

    // Следующий слой (выходной)
    auto hiddenPtr = std::make_shared<Layer>(hidden);
    Layer output(hiddenPtr, 2, 0.1, math::sigmoid, math::sigmoid_derivative);

    // Прямой проход (значения не важны, главное — заполнить кэш)
    std::vector<double> x = { 0.3, 0.7 };
    auto hiddenOut = hidden.Forward(x);
    auto outOut = output.Forward(hiddenOut);

    std::vector<double> expected = { 0.0, 1.0 };
    output.CalcDelta(expected);

    // Вычисляем дельты скрытого слоя
    hidden.CalcDelta(output);

    for (const auto& n : hidden._neurons) {
        EXPECT_TRUE(std::isfinite(n._delta));
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
