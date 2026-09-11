#include "neuron/Network.hpp"

#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <vector>

#include "neuron/Layer.hpp"
#include "neuron/common.hpp"

namespace neuron {

Network::Network(std::vector<size_t> mapLayers, double learningRate,
    ActivationFunction activation, ActivationFunction activationDerivative)
{
    if (mapLayers.size() < 3)
        throw std::invalid_argument("mapLayers must have at least 3 layers");

    // входной слой
    auto inputLayer = std::make_shared<Layer>(nullptr, mapLayers[0], learningRate, activation, activationDerivative);
    _layers.push_back(inputLayer);

    // скрытые слои и выходной слой
    for (size_t i = 1; i < mapLayers.size(); ++i) {
        auto layer = std::make_shared<Layer>(_layers.back(), mapLayers[i], learningRate, activation, activationDerivative);
        _layers.push_back(layer);
    }
}

std::vector<double> Network::Forward(const std::vector<double>& input)
{
    std::vector<double> output = input;
    for (const auto& layer : _layers) {
        output = layer->Forward(output);
    }

    return output;
}

void Network::Backward(const common::vector_m2<double>& output, const common::vector_m2<double>& target)
{
    for (size_t i = 0; i < output.size(); ++i) {
        auto xs = output[i];
        auto ys = target[i];

        Forward(xs);
        _Backpropagate(ys);
        _UpdateWeights();
    }
}

void Network::_Backpropagate(const std::vector<double>& target)
{
    auto outputLayer = _layers.back();
    outputLayer->CalcDelta(target);

    for (size_t i = _layers.size() - 1; i >= 0; --i) {
        auto layer = _layers[i];
        auto nextLayer = _layers[i + 1];

        layer->CalcDelta(*nextLayer);
    }
}

void Network::_UpdateWeights()
{
    // TODO Добавить методы обновления весов для Layer и Neuron

    for (size_t layerIndex = 1; layerIndex < _layers.size(); ++layerIndex) {
        auto& layer = *_layers[layerIndex];
        assert(layer._prevLayer != nullptr);

        const auto& prevOutput = layer._prevLayer->_cache;

        for (auto& neuron : layer._neurons) {
            assert(neuron._weights.size() == prevOutput.size());

            for (size_t w = 0; w < neuron._weights.size(); ++w) {
                neuron._weights[w] += neuron._learningRate * prevOutput[w] * neuron._delta;
            }
        }
    }
}

}
