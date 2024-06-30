#pragma once

#include <memory>
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

    std::vector<double> getWeights() const;

    double getOutput() const;

    double getDelta() const;
    void setDelta(double delta);

    ActivationFunction getActivationFn() const;
    ActivationFunction getActivationDerivativeFn() const;

    double forward(const std::vector<double>& inputs);
};

class Layer {
private:
    std::shared_ptr<Layer> prevLayer_;

    std::vector<Neuron> neurons_;
    std::vector<double> outputs_;

public:
    Layer(std::shared_ptr<Layer> prevLayer, int numNeurons, int learningRate,
        ActivationFunction activationFn, ActivationFunction activationDerivativeFn);

    void forward(const std::vector<double>& inputs);

    void calculateDeltas(const std::vector<double>& targets); // call only for output layer
    void calculateDeltas(const Layer& nextLayer);
};

}

namespace neuron::math {

double dotProduct(const std::vector<double>& xs, const std::vector<double>& ys);

double sigmoid(double x);
double derivativeSigmoid(double x);

}
