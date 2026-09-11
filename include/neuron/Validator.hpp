#pragma once

#include <vector>

#include "neuron/Network.hpp"
#include "neuron/common.hpp"

namespace neuron {

struct ValidateResult {
    const int correct;
    const int trails;
    const double percentage;

    ValidateResult(int correct_, int trails_, double percentage_)
        : correct(correct_)
        , trails(trails_)
        , percentage(percentage_)
    {
    }
};

template <typename T>
using ValidationFunction = T (*)(const std::vector<double>&);

template <typename T>
struct Validator {
    ValidationFunction<T> _validate;

    Validator(ValidationFunction<T> validate)
        : _validate(validate)
    {
    }

    ValidateResult Validate(Network& net,
        const common::vector_m2<double>& inputs, const std::vector<T>& targets)
    {
        double correct = 0.0;
        for (size_t i = 0; i < inputs.size(); ++i) {
            auto input = inputs.at(i);
            auto target = targets.at(i);

            auto result = _validate(net.Forward(input));
            if (result == target)
                ++correct;
        }

        double percentage = (double)correct / targets.size();

        return ValidateResult(correct, inputs.size(), percentage);
    }
};

}
