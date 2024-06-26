#include "neuron.hpp"

#include "cmath"

namespace neuron::math {

double dotProduct(const std::vector<double>& xs, const std::vector<double>& ys)
{
    double result = 0.0;
    for (int i = 0; i < xs.size(); i++) {
        result += xs[i] * ys[i];
    }
    return result;
}

double sigmoid(double x)
{
    return 1.0 / (1.0 + std::exp(-x));
}

double derivativeSigmoid(double x)
{
    return sigmoid(x) * (1.0 - sigmoid(x));
}

}