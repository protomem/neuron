#pragma once

namespace neuron {

class Neuron {
public:
    Neuron();
    ~Neuron();
};

}

namespace neuron::math {

double dotProduct(const std::vector<double> &a, const std::vector<double> &b);

}
