#pragma once

#include <cmath>
#include <vector>
namespace neuron::math {

double dot_product(const std::vector<double>& a, const std::vector<double>& b);

double sigmoid(double x);
double sigmoid_derivative(double x);

}
