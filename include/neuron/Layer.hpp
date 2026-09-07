#pragma once

#include <cstddef>
#include <memory>
#include <vector>

#include "neuron/Neuron.hpp"

namespace neuron {

struct Layer {
    std::shared_ptr<Layer> _prevLayer;
    std::vector<Neuron> _neurons;
    std::vector<double> _cache;

    Layer(std::shared_ptr<Layer> prevLayer, size_t numNeurons, double learningRate,
        ActivationFunction activation, ActivationFunction activationDerivative)
        : _prevLayer(prevLayer)
        , _neurons(NeuronFabric::CreateNeurons(
              numNeurons, prevLayer == nullptr ? 0 : numNeurons,
              learningRate, activation, activationDerivative))
        , _cache(numNeurons)
    {
    }

    std::vector<double> Forward(const std::vector<double>& inputs);

    void CalcDelta(std::vector<double> expected);
    void CalcDelta(Layer& nextLayer);
};

}
