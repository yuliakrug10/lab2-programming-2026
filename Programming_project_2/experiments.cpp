#include "experiments.h"
#include "timer.h"        
#include "parallel_alg.h"
#include <iostream>
#include <format>
#include <algorithm>
#include <execution>
#include <thread>

using namespace std;

void run_experiments(const vector<int>& data, const string& ds_name) {
    cout << format("\nExperiments for dataset: {} (size of dataset: {})", ds_name, data.size()) << endl;
    int result = 0;
    double time_ms = 0;

    time_ms = measure_time([&]() { return min_element(data.begin(), data.end()); }, result);
    cout << format("\nmin_element (no policy): ms = {} | result = {}", time_ms, result) << endl;

    time_ms = measure_time([&]() { return min_element(execution::seq, data.begin(), data.end()); }, result);
    cout << format("min_element (execution::seq): ms = {} | result = {}", time_ms, result) << endl;

    time_ms = measure_time([&]() { return min_element(execution::par, data.begin(), data.end()); }, result);
    cout << format("min_element (execution::par): ms = {} | result = {}", time_ms, result) << endl;

    time_ms = measure_time([&]() { return min_element(execution::par_unseq, data.begin(), data.end()); }, result);
    cout << format("min_element (execution::par_unseq): ms = {} | result = {}\n", time_ms, result) << endl;

    cout << "Parallel algorithm results:" << endl;
    cout << string(50, '-') << endl;
    cout << format("| {:^10} | {:^15} | {:^14} |", "threads (K)", "time (ms)", "result") << endl;
    cout << string(50, '-') << endl;

    vector<int> K_values = { 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 16, 24, 32, 64, 128, 256, 512, 1024 };

    double best_time = 0;
    int best_k = 1;
    bool is_first = true;

    for (int k : K_values) {
        time_ms = measure_time([&]() { return parallel_min(data.begin(), data.end(), k); }, result);

        cout << format("| {:<10} | {:<15.4f} | {:<14} |\n", k, time_ms, result);

        if (is_first || time_ms < best_time) {
            best_time = time_ms;
            best_k = k;
            is_first = false;
        }
    }
    cout << string(50, '-') << endl;

    unsigned int hw_threads = thread::hardware_concurrency();
    cout << format("\nResults for {}:", ds_name) << endl;
    cout << format("\nCPU Cores: {}", hw_threads) << endl;
    cout << format("Best speed at K = {} ({:.4f} ms)", best_k, best_time) << endl;
    cout << format("Ratio to the number of processor threads: {:.4f}", double(best_k) / hw_threads) << endl;
}