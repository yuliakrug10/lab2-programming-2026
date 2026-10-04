#include "file_operations.h"
#include <random>
#include <fstream>
#include <iostream>
#include <limits>

void make_random_seq(const std::string& filename, size_t size) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    std::ofstream output(filename);

    if (!output) {
        std::cerr << "Error, can't open file for writing " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < size; i++) {
        output << dist(gen);
        if (i != size - 1) {
            output << " ";
        }
    }
}

std::vector<int> seq_in_vector(const std::string& filename) {
    std::vector<int> data;
    std::ifstream input(filename);

    if (!input) {
        std::cerr << "Error, can't open file for reading " << filename << std::endl;
        return data;
    }

    int value;
    while (input >> value) {
        data.push_back(value);
    }
    return data;
}