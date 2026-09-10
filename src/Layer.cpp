#include "neuron/Layer.hpp"

#include <cassert>
#include <cstddef>
#include <vector>

namespace neuron {

std::vector<double> Layer::Forward(const std::vector<double>& inputs)
{
    if (_prevLayer) {
        // Для скрытых/выходных слоёв
        assert(inputs.size() == _prevLayer->_cache.size());
        assert(_neurons.size() == _cache.size());
    } else {
        // Для входного слоя
        assert(inputs.size() == _cache.size());
    }

    if (_prevLayer != nullptr) {
        for (size_t i = 0; i < _neurons.size(); i++) {
            _cache[i] = _neurons[i].Forward(inputs);
        }
    } else {
        _cache = inputs;
    }

    return _cache;
}

void Layer::CalcDelta(std::vector<double> target)
{
    assert(target.size() == _neurons.size());
    assert(_neurons.size() == _cache.size());

    for (size_t i = 0; i < _neurons.size(); i++) {
        auto neuron = _neurons[i];
        double currentDelta = target[i] - _cache[i];

        neuron.SetDelta(neuron.CallActivationDerivative() * currentDelta);
    }
}

void Layer::CalcDelta(Layer& nextLayer)
{
    assert(!_neurons.empty());
    assert(!nextLayer._neurons.empty());

    for (size_t i = 0; i < _neurons.size(); ++i) {
        auto neuron = _neurons[i];
        double sumWeightsAndDeltas = 0.0;

        for (const auto& nextNeuron : nextLayer._neurons) {
            assert(i < nextNeuron._weights.size());
            sumWeightsAndDeltas += nextNeuron._weights[i] * nextNeuron._delta;
        }

        neuron.SetDelta(neuron.CallActivationDerivative() * sumWeightsAndDeltas);
    }
}

}
