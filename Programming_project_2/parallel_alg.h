#pragma once
#include <thread>
#include <vector>
#include <algorithm>
#include <iterator>

template<typename ForwIter>
ForwIter parallel_min(ForwIter first, ForwIter last, int K) {
    auto dist = std::distance(first, last);
    if (dist == 0) return last;
    if (K <= 1 || dist < K) return std::min_element(first, last);

    auto piece_size = dist / K;
    std::vector<std::thread> threads;
    std::vector<ForwIter> local_mins(K);

    auto current = first;
    for (int i = 0; i < K; ++i) {
        ForwIter next;

        if (i == K - 1) {
            next = last;
        }
        else {
            next = std::next(current, piece_size);
        }

        threads.emplace_back([&local_mins, i, current, next]() {
            local_mins[i] = std::min_element(current, next);
            });

        current = next;
    }

    for (auto& t : threads) {
        t.join();
    }

    auto global_min_it = std::min_element(local_mins.begin(), local_mins.end(),
        [](ForwIter a, ForwIter b) { return *a < *b; });

    return *global_min_it;
}