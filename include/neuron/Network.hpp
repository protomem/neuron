#pragma once

#include <memory>
#include <vector>

#include "neuron/Layer.hpp"
#include "neuron/Neuron.hpp"
#include "neuron/common.hpp"

namespace neuron {

struct ValidateResult {
    const int correct;
    const int trails;
    const double percentage;

    ValidateResult(int correct_, int trails_, double percentage_)
        : correct(correct_)
        , trails(trails_)
        , percentage(percentage_)
    {
    }
};

template <typename T>
using ValidationFunction = T (*)(const std::vector<double>&);

template <typename T>
struct Network {
    std::vector<std::shared_ptr<Layer>> _layers;

    Network(std::vector<size_t> mapLayers, double learningRate,
        ActivationFunction activation, ActivationFunction activationDerivative);

    std::vector<double> Forward(const std::vector<double>& input);
    ValidateResult Validate(ValidationFunction<T> validate,
        const common::vector_m2<double>& inputs, const std::vector<T>& targets);

    void Backward(const common::vector_m2<double>& output, const common::vector_m2<double>& target);
    void _Backpropagate(const std::vector<double>& target);
    void _UpdateWeights();
};

}
