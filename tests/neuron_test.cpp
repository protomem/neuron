#include <cmath>
#include <gtest/gtest.h>

#include "neuron.hpp"

TEST(NetworkTest, ValidateCountsCorrectAndPercentage)
{
    using namespace neuron;

    // Сеть 2-2-1 с сигмоидой
    Network<int> net({ 2, 2, 1 }, 0.1, math::sigmoid, math::sigmoid_derivative);

    // Валидационная функция: считает, что класс 1, если выход > 0.5
    auto validateFn = [](const std::vector<double>& output) -> int {
        return output[0] > 0.5 ? 1 : 0;
    };

    // Два примера: один ожидаемо верный, другой, скорее всего, нет
    common::vector_m2<double> inputs = {
        { 1.0, 1.0 },
        {
            -1.0,
            -1.0,
        },
    };

    std::vector<int> targets = {
        1,
        0,
    };

    auto result = net.Validate(validateFn, inputs, targets);

    EXPECT_EQ(result.trails, 2);
    EXPECT_GE(result.correct, 0);
    EXPECT_LE(result.correct, 2);
    EXPECT_GE(result.percentage, 0.0);
    EXPECT_LE(result.percentage, 1.0);
}

TEST(NeuronVersionTest, ValidateVersion)
{
    const auto v = neuron::version();
    EXPECT_FALSE(v.empty());
}

TEST(NeuronTest, ForwardWithKnownWeights)
{
    using namespace neuron;

    std::vector<double> weights = { 1.0, 2.0, -1.0 };
    Neuron n(weights, /*learningRate*/ 0.1, math::sigmoid,
        math::sigmoid_derivative);

    std::vector<double> input = { 2.0, 0.5, 1.0 };
    // dot = 2*1 + 0.5*2 + 1*(-1) = 2 + 1 - 1 = 2
    double out = n.Forward(input);

    EXPECT_DOUBLE_EQ(out, math::sigmoid(2.0));
}

TEST(MathTest, DotProductBasic)
{
    using neuron::math::dot_product;

    std::vector<double> a = { 1.0, 2.0, 3.0 };
    std::vector<double> b = { 4.0, -1.0, 0.5 };
    // 1*4 + 2*(-1) + 3*0.5 = 4 - 2 + 1.5 = 3.5
    double result = dot_product(a, b);

    EXPECT_DOUBLE_EQ(result, 3.5);
}

TEST(MathTest, SigmoidAtZero)
{
    using neuron::math::sigmoid;

    double result = sigmoid(0.0);
    EXPECT_DOUBLE_EQ(result, 0.5);
}

TEST(MathTest, SigmoidDerivativeAtZero)
{
    using neuron::math::sigmoid;
    using neuron::math::sigmoid_derivative;

    double x = 0.0;
    double expected = sigmoid(x) * (1.0 - sigmoid(x));
    EXPECT_DOUBLE_EQ(sigmoid_derivative(x), expected);
}

TEST(NeuronTest, SetDeltaAndCallActivation)
{
    using namespace neuron;

    std::vector<double> weights = { 1.0, 1.0 };
    Neuron n(weights, /*learningRate*/ 0.1, math::sigmoid,
        math::sigmoid_derivative);

    // Проверяем SetDelta
    n.SetDelta(0.42);
    EXPECT_DOUBLE_EQ(n._delta, 0.42);

    // Устанавливаем кэш и проверяем вызовы активации
    n._cache = 1.5;
    double act = n.CallActivation();
    double actDeriv = n.CallActivationDerivative();

    EXPECT_DOUBLE_EQ(act, math::sigmoid(1.5));
    EXPECT_DOUBLE_EQ(actDeriv, math::sigmoid_derivative(1.5));
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
