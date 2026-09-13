#pragma once

#include "neuron/common.hpp"
#include <string>

namespace neuron {

void normalize_by_feature_scale(common::vector_m2<double>& dataset);

common::vector_m2<std::string> load_dataset_csv(const std::string& path);

}
