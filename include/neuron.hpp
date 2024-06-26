#pragma once

#include <vector>

namespace neuron {

using ActivationFunction = double (*)(double);

class Neuron {
private:
    const double learningRate_;

    std::vector<double> weights_;

    double output_;
    double delta_;

    ActivationFunction activationFn_;
    ActivationFunction activationDerivativeFn_;

public:
    Neuron(std::vector<double> weights, double learningRate,
        ActivationFunction activationFn, ActivationFunction activationDerivativeFn);

    double forward(const std::vector<double>& inputs);
};

}

namespace neuron::math {

double dotProduct(const std::vector<double>& xs, const std::vector<double>& ys);

double sigmoid(double x);
double derivativeSigmoid(double x);

}
