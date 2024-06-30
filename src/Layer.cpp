#include "neuron.hpp"

#include <cstdlib>
#include <vector>

namespace neuron {

Layer::Layer(std::shared_ptr<Layer> prevLayer, int numNeurons, int learningRate,
    ActivationFunction activationFn, ActivationFunction activationDerivativeFn)
    : prevLayer_(prevLayer)
    , neurons_(std::vector<Neuron>())
    , outputs_(std::vector<double>(numNeurons, 0.0))
{
    for (int i = 0; i < numNeurons; i++) {
        auto weights = std::vector<double>();
        if (prevLayer != nullptr) {
            // TODO: Better randomization
            std::srand(time(NULL));
            for (int j = 0; j < prevLayer->neurons_.size(); j++) {
                weights.push_back(static_cast<double>(std::rand()) / RAND_MAX);
            }
        }

        neurons_.push_back(Neuron(weights, learningRate, activationFn, activationDerivativeFn));
    }
}

void Layer::forward(const std::vector<double>& inputs)
{
    if (prevLayer_ == nullptr) {
        outputs_ = inputs;
    } else {
        for (int i = 0; i < neurons_.size(); i++) {
            outputs_[i] = neurons_[i].forward(inputs);
        }
    }
}

void Layer::calculateDeltas(const std::vector<double>& targets)
{
    for (int i = 0; i < neurons_.size(); i++) {
        neurons_[i].setDelta(
            neurons_[i].getActivationDerivativeFn()(neurons_[i].getOutput())
            - (targets[i] - outputs_[i]));
    }
}

void Layer::calculateDeltas(const Layer& nextLayer)
{
    for (int i = 0; i < neurons_.size(); i++) {
        std::vector<double> nextWeights;
        for (int j = 0; j < nextLayer.neurons_.size(); j++) {
            nextWeights.push_back(nextLayer.neurons_[j].getWeights()[i]);
        }

        std::vector<double> nextDeltas;
        for (int j = 0; j < nextLayer.neurons_.size(); j++) {
            nextDeltas.push_back(nextLayer.neurons_[j].getDelta());
        }

        double sum = math::dotProduct(nextWeights, nextDeltas);
        neurons_[i].setDelta(
            neurons_[i].getActivationDerivativeFn()(neurons_[i].getOutput())
            * sum);
    }
}

}