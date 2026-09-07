#include "neuron/Neuron.hpp"

#include <cassert>
#include <random>
#include <vector>

#include "neuron/math.hpp"

namespace neuron {

double Neuron::Forward(const std::vector<double>& inputs)
{
    assert(inputs.size() == _weights.size());

    _cache = math::dot_product(inputs, _weights);
    return _activation(_cache);
}

std::vector<Neuron> NueronFabric::CreateNeurons(size_t numNeurons,
    size_t numInputs, double learningRate, ActivationFunction activation,
    ActivationFunction activationDerivative)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    std::vector<Neuron> neurons;
    neurons.reserve(numNeurons);

    for (size_t i = 0; i < numNeurons; ++i) {
        std::vector<double> weights(numInputs);
        for (size_t j = 0; j < numInputs; ++j) {
            weights[j] = dist(gen);
        }
        neurons.emplace_back(weights, learningRate, activation, activationDerivative);
    }

    return neurons;
}

}
