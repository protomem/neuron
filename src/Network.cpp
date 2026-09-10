#include "neuron/Network.hpp"

#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <vector>

#include "neuron/Layer.hpp"
#include "neuron/common.hpp"

namespace neuron {

template <typename T>
Network<T>::Network(std::vector<size_t> mapLayers, double learningRate,
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

template <typename T>
std::vector<double> Network<T>::Forward(const std::vector<double>& input)
{
    std::vector<double> output = input;
    for (const auto& layer : _layers) {
        output = layer->Forward(output);
    }

    return output;
}

template <typename T>
void Network<T>::Backward(const common::vector_m2<double>& output, const common::vector_m2<double>& target)
{
    for (size_t i = 0; i < output.size(); ++i) {
        auto xs = output[i];
        auto ys = target[i];

        Forward(xs);
        _Backpropagate(ys);
        _UpdateWeights();
    }
}

template <typename T>
void Network<T>::_Backpropagate(const std::vector<double>& target)
{
    auto outputLayer = _layers.back();
    outputLayer->CalcDelta(target);

    for (size_t i = _layers.size() - 1; i >= 0; --i) {
        auto layer = _layers[i];
        auto nextLayer = _layers[i + 1];

        layer->CalcDelta(*nextLayer);
    }
}

template <typename T>
void Network<T>::_UpdateWeights()
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

template <typename T>
ValidateResult Network<T>::Validate(ValidationFunction<T> validate,
    const common::vector_m2<double>& inputs, const std::vector<T>& targets)
{
    int correct = 0;
    for (size_t i = 0; i < inputs.size(); ++i) {
        auto input = inputs.at(i);
        auto target = targets.at(i);

        auto result = validate(Forward(input));
        if (result == target)
            ++correct;
    }

    double percentage = (double)correct / targets.size();

    return ValidateResult(correct, inputs.size(), percentage);
}

}

template struct neuron::Network<int>;
