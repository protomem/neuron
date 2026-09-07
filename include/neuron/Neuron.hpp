#pragma once

#include <cstddef>
#include <vector>

namespace neuron {

using ActivationFunction = double (*)(double);

struct Neuron {
    std::vector<double> _weights;

    double _learningRate;
    double _delta = 0;

    double _cache = 0;

    ActivationFunction _activation;
    ActivationFunction _activationDerivative;

    Neuron(std::vector<double> weights, double learningRate,
        ActivationFunction activation, ActivationFunction activationDerivative)
        : _weights(weights)
        , _learningRate(learningRate)
        , _activation(activation)
        , _activationDerivative(activationDerivative)
    {
    }

    Neuron(double learningRate,
        ActivationFunction activation, ActivationFunction activationDerivative)
        : Neuron(std::vector<double>(0), learningRate, activation, activationDerivative)
    {
    }

    void SetDelta(double delta)
    {
        _delta = delta;
    }

    double CallActivation()
    {
        if (!_activation)
            return 0;

        return _activation(_cache);
    }

    double CallActivationDerivative()
    {
        if (!_activationDerivative)
            return 0;

        return _activationDerivative(_cache);
    }

    double Forward(const std::vector<double>& inputs);
};

struct NeuronFabric {
    static std::vector<Neuron> CreateNeurons(size_t numNeurons,
        size_t numInputs, double learningRate, ActivationFunction activation,
        ActivationFunction activationDerivative);
};

}
