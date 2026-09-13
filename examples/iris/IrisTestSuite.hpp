#pragma once

#include <algorithm>

#include "neuron/Network.hpp"
#include "neuron/Validator.hpp"
#include "neuron/common.hpp"
#include "neuron/dataset.hpp"
#include "neuron/math.hpp"

using namespace neuron;

struct IrisTestSuite {
    inline static const std::string IRIS_SETOSA = "Iris-setosa";
    inline static const std::string IRIS_VERSICOLOR = "Iris-versicolor";
    inline static const std::string IRIS_VIRGINICA = "Iris-virginica";

    common::vector_m2<double> _parametrs;
    common::vector_m2<double> _classification;
    std::vector<std::string> _species;

    IrisTestSuite(const std::string& path)
    {
        auto dataset = load_dataset_csv(path);
        common::shuffle_rand(dataset);

        for (const auto& iris : dataset) {
            if (iris.size() < 5) {
                continue;
            }

            const bool has_id_column = iris.size() >= 6;
            const size_t feature_start = has_id_column ? 1 : 0;
            const size_t species_index = has_id_column ? 5 : 4;

            if (iris.size() <= species_index || iris.size() < feature_start + 4) {
                continue;
            }

            std::vector<double> parameters;
            parameters.reserve(4);

            bool valid_row = true;
            for (size_t i = 0; i < 4; ++i) {
                try {
                    parameters.push_back(std::stod(iris.at(feature_start + i)));
                } catch (...) {
                    valid_row = false;
                    break;
                }
            }

            if (!valid_row) {
                continue;
            }

            const auto& species = iris.at(species_index);
            std::vector<double> classification;

            if (species == IRIS_SETOSA) {
                classification = { 1.0, 0.0, 0.0 };
            } else if (species == IRIS_VERSICOLOR) {
                classification = { 0.0, 1.0, 0.0 };
            } else if (species == IRIS_VIRGINICA) {
                classification = { 0.0, 0.0, 1.0 };
            } else {
                continue;
            }

            _parametrs.push_back(std::move(parameters));
            _classification.push_back(std::move(classification));
            _species.push_back(species);
        }

        if (!_parametrs.empty()) {
            normalize_by_feature_scale(_parametrs);
        }
    }

    static std::string Validate(const std::vector<double>& output)
    {
        double maximum = *std::max_element(output.begin(), output.end());
        if (maximum == output.at(0))
            return IRIS_SETOSA;
        else if (maximum == output.at(1))
            return IRIS_VERSICOLOR;
        else
            return IRIS_VIRGINICA;
    }

    ValidateResult Classify()
    {
        Network net({ 4, 6, 3 }, 0.3, math::sigmoid, math::sigmoid_derivative);

        auto trainers = common::copy_sublist(_parametrs, 0, 140);
        auto trainerCorrects = common::copy_sublist(_classification, 0, 140);

        size_t trains = 50;
        for (size_t i = 0; i < trains; ++i)
            net.Backward(trainers, trainerCorrects);

        auto testers = common::copy_sublist(_parametrs, 140, 150);
        auto testerCorrects = common::copy_sublist(_species, 140, 150);

        Validator<std::string> validator(Validate);
        return validator.Validate(net, testers, testerCorrects);
    }
};
