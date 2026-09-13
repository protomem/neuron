#include "neuron/dataset.hpp"

#include <fstream>
#include <stdexcept>
#include <string>

namespace neuron {

void normalize_by_feature_scale(common::vector_m2<double>& dataset)
{
    for (size_t column_num = 0; column_num < dataset.at(0).size(); ++column_num) {
        std::vector<double> column;
        column.reserve(dataset.size());

        for (auto& row : dataset) {
            column.push_back(row.at(column_num));
        }

        double maximum = *std::max_element(column.begin(), column.end());
        double minimum = *std::min_element(column.begin(), column.end());
        double difference = maximum - minimum;

        for (auto& row : dataset) {
            row.at(column_num) = (row.at(column_num) - minimum) / difference;
        }
    }
}

common::vector_m2<std::string> load_dataset_csv(const std::string& path)
{
    common::vector_m2<std::string> dataset;

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("file is not open");
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.empty()) {
            continue;
        }

        std::vector<std::string> row;
        std::string cell;
        bool in_quotes = false;

        for (size_t i = 0; i < line.size(); ++i) {
            const char ch = line[i];

            if (ch == '"') {
                if (in_quotes && i + 1 < line.size() && line[i + 1] == '"') {
                    cell.push_back('"');
                    ++i;
                } else {
                    in_quotes = !in_quotes;
                }
                continue;
            }

            if (ch == ',' && !in_quotes) {
                row.push_back(cell);
                cell.clear();
                continue;
            }

            cell.push_back(ch);
        }

        row.push_back(cell);
        dataset.push_back(std::move(row));
    }

    return dataset;
}

}
