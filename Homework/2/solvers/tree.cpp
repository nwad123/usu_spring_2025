#include "solvers/tree.hpp"

#include <algorithm>
#include <thread>

namespace hpc {
[[nodiscard]] auto Tree::operator()(const Config &config, const std::span<fp> dataset) const -> Bin {
    using std::thread;
    using std::ref;

    auto task = [&config, &dataset](/*in*/ size_t id, /*in*/ const std::span<fp> ranges, /*out*/ Bin &bin) {
        const auto num_elements = config.size / config.threads;
        const auto starting_element = id * num_elements;

        const auto dataset_slice = [&]() {
            // in the case that we cannot evenly divide our data elements between threads
            // we need to ensure that the last thread picks up the extra elements that were
            // not allocated a thread
            const auto max_thread_id = config.threads - 1;
            if (id < max_thread_id) {
                return dataset.subspan(starting_element, num_elements);
            } else {
                return dataset.subspan(starting_element);
            }
        }();

        bin.maxes.resize(config.bins);
        bin.counts.resize(config.bins);

        auto insert = [&ranges, &bin](const fp value) {
            auto bin_it = std::upper_bound(ranges.begin(), ranges.end(), value);
            auto index = std::distance(ranges.begin(), bin_it);

            bin.counts[index]++;
            if (bin.maxes[index] < value) { bin.maxes[index] = value; }
        };

        for (const auto data : dataset_slice) { insert(data); }
    };

    std::vector<fp> ranges(config.bins);
    fp f{ config.max };
    fp diff{ (config.max - config.min) / static_cast<fp>(config.bins) };

    for (auto it = ranges.rbegin(); it != ranges.rend(); ++it) {
        auto &range = *it;
        range = f;
        f -= diff;
    }

    std::vector<Bin> bins{ config.threads };
    std::vector<thread> threads{};
    threads.reserve(config.threads);

    for (size_t id = 0; id < config.threads; id++) {
        threads.push_back(thread{ task, id, std::span{ ranges }, ref(bins[id]) });
    }

    for (auto &thread : threads) { thread.join(); }

    Bin output{};
    output.maxes.resize(config.bins);
    output.counts.resize(config.bins);

    for (auto &bin : bins) {
        for (size_t i = 0; i < config.bins; i++) {
            output.maxes[i] = std::max(bin.maxes[i], output.maxes[i]);
            output.counts[i] += bin.counts[i];
        }
    }

    return output;
}
}// namespace hpc
