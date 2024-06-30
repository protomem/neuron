#include "neuron.hpp"

namespace neuron {

Neuron::Neuron(std::vector<double> weights, double learningRate,
    ActivationFunction activationFn, ActivationFunction activationDerivativeFn)
    : learningRate_(learningRate)
    , weights_(weights)
    , output_(0.0)
    , delta_(0.0)
    , activationFn_(activationFn)
    , activationDerivativeFn_(activationDerivativeFn)
{
}

double Neuron::getDelta() const
{
    return delta_;
}

void Neuron::setDelta(double delta)
{
    delta_ = delta;
}

ActivationFunction Neuron::getActivationFn() const
{
    return activationFn_;
}

ActivationFunction Neuron::getActivationDerivativeFn() const
{
    return activationDerivativeFn_;
}

double Neuron::forward(const std::vector<double>& inputs)
{
    output_ = math::dotProduct(weights_, inputs);
    return activationFn_(output_);
}

}
