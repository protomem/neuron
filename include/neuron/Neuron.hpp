#pragma once

#include <vector>
namespace neuron {

using ActivationFunction = double (*)(double);

struct Neuron {
    std::vector<double> _weights;

    double _learning_rate;
    double _delta;

    double _cache;

    ActivationFunction _activation;
    ActivationFunction _activation_derivative;

    Neuron(std::vector<double> weights, double learning_rate,
        ActivationFunction activation, ActivationFunction activation_derivative)
        : _weights(weights)
        , _learning_rate(learning_rate)
        , _activation(activation)
        , _activation_derivative(activation_derivative)
    {
    }

    double Forward(const std::vector<double>& inputs);
};

}
