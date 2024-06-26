#pragma 

#include "neuron.hpp"

namespace neuron::math {

double dotProduct(const std::vector<double> &xs, const std::vector<double> &ys) {
    double result = 0.0;
    for (int i = 0; i < xs.size(); i++) {
        result += xs[i] * ys[i];
    }
    return result;
}

}