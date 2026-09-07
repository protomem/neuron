#include "neuron/Neuron.hpp"

#include <cassert>

#include "neuron/math.hpp"

namespace neuron {

double Neuron::Forward(const std::vector<double>& inputs)
{
    assert(inputs.size() == _weights.size());

    _cache = math::dot_product(inputs, _weights);
    return _activation(_cache);
}

}
