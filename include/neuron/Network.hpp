#pragma once

#include <memory>
#include <vector>

#include "neuron/Layer.hpp"
#include "neuron/Neuron.hpp"
#include "neuron/common.hpp"

namespace neuron {

struct Network {
    std::vector<std::shared_ptr<Layer>> _layers;

    Network(std::vector<size_t> mapLayers, double learningRate,
        ActivationFunction activation, ActivationFunction activationDerivative);

    std::vector<double> Forward(const std::vector<double>& input);

    void Backward(const common::vector_m2<double>& output, const common::vector_m2<double>& target);
    void _Backpropagate(const std::vector<double>& target);
    void _UpdateWeights();
};

}
