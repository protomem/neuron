#pragma once

#include <algorithm>
#include <cstddef>
#include <random>
#include <vector>

namespace neuron::common {

template <typename T>
using vector_m2 = std::vector<std::vector<T>>;

template <typename T>
inline std::vector<T> copy_sublist(const std::vector<T>& src, size_t begin, size_t end)
{
    if (begin >= src.size() || begin >= end) {
        return {};
    }

    end = std::min(end, src.size());
    return std::vector<T>(src.begin() + static_cast<std::ptrdiff_t>(begin),
        src.begin() + static_cast<std::ptrdiff_t>(end));
}

template <typename T>
inline void shuffle_rand(std::vector<T>& collection)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::shuffle(collection.begin(), collection.end(), gen);
}

template <typename T = std::string>
inline std::string collect_content(const std::vector<T>& src, const std::string delim)
{
    std::string accumulator(src.begin(), src.end());
    return accumulator;
}

}
