// MSVC v143 (version 19.44.35228, 32-bit x86)
// Kruhlienia Yulia K-28

#include <iostream>
#include "file_operations.h"
#include "experiments.h"
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<pair<string, size_t>> datasets = {
        {"data_small.txt",   100000},
        {"data_large.txt", 10000000}
    };

    for (const auto& ds : datasets) {
        make_random_seq(ds.first, ds.second);
    }

    for (const auto& ds : datasets) {
        vector<int> data = seq_in_vector(ds.first);
        if (!data.empty()) {
            run_experiments(data, ds.first);
        }
    }
	return 0;
}