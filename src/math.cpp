#include "neuron/math.hpp"

#include <cassert>
#include <cmath>

namespace neuron::math {

double dot_product(const std::vector<double>& xs, const std::vector<double>& ys)
{
    assert(xs.size() <= ys.size());

    double sum = 0.0;
    for (size_t i = 0; i < xs.size(); ++i) {
        sum += xs[i] * ys[i];
    }

    return sum;
}

double sigmoid(double x)
{
    return 1.0 / (1.0 + std::exp(-x));
}

double sigmoid_derivative(double x)
{
    return sigmoid(x) * (1.0 - sigmoid(x));
}

}
