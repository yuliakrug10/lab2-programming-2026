#pragma once
#include <chrono>

template<typename Func>
double measure_time(Func&& func, int& result_val) {
    auto start = std::chrono::high_resolution_clock::now();
    auto it = func();
    auto end = std::chrono::high_resolution_clock::now();

    result_val = *it;
    return std::chrono::duration<double, std::milli>(end - start).count();
}