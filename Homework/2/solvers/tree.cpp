#include "solvers/tree.hpp"

#include <algorithm>
#include <bit>
#include <semaphore>
#include <thread>
#include <ranges>

namespace hpc {

class simple_semaphore
{
  private:
    std::binary_semaphore sem_;

  public:
    constexpr simple_semaphore() : sem_(0) {}

    constexpr auto acquire() -> void { sem_.acquire(); }
    constexpr auto release() -> void { sem_.release(); }
};

[[nodiscard]] auto Tree::operator()(const Config &config, const std::span<fp> dataset) const -> Bin
{
    using std::thread;
    using std::ref;

    // OPTIMIZE: this whole function works fine but definitely does some extra work.
    auto get_recieves = [&config](/*in*/ const size_t id) -> std::vector<size_t> {
        std::vector<size_t> output;

        if (id == 0) {
            size_t init = 1;
            while (init < config.threads) {
                output.push_back(init);
                init <<= 1;
            }
        } else if (id % 2 == 0) {
            const size_t upper_bound = [&]() {
                const size_t next_power_of_2 = std::bit_ceil(id + 1);
                return std::min(config.threads, next_power_of_2);
            }();

            // OPTIMIZE: this for-loop is wasteful, and does many empty iterations because
            // `n` is often much greater than `config.size`
            for (size_t j = 0; j < config.threads - id; j++) {
                const size_t x = 1 << j;
                const size_t n = id + x;
                if (id % x == 0 and n < upper_bound) { output.push_back(n); }
            }
        }

        return output;
    };

    std::vector<simple_semaphore> senders(config.size);
    std::vector<simple_semaphore> receivers(config.size);


    std::vector<fp> ranges(config.bins);
    fp f{ config.max };
    fp diff{ (config.max - config.min) / static_cast<fp>(config.bins) };

    for (auto it = ranges.rbegin(); it != ranges.rend(); ++it) {
        auto &range = *it;
        range = f;
        f -= diff;
    }

    std::vector<Bin> bins{ config.threads };

    auto task = [&config, &dataset, &get_recieves, &senders, &receivers, &bins](
                    /*in*/ size_t id, /*in*/ const std::span<fp> ranges, /*out*/ Bin &bin) -> void {
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

        // Receiving all the data
        const auto recv_list = get_recieves(id);

        for (const auto recv_id : recv_list) {
            senders[recv_id].acquire();

            const auto &recv_bin = bins[recv_id];

            for (size_t i = 0; i < config.bins; i++) {
                bin.maxes[i] = std::max(bin.maxes[i], recv_bin.maxes[i]);
                bin.counts[i] += recv_bin.counts[i];
            }

            receivers[recv_id].release();
        }

        senders[id].release();
        receivers[id].acquire();
        return;
    };

    std::vector<thread> threads{};
    threads.reserve(config.threads);

    for (size_t id = 0; id < config.threads; id++) {
        threads.push_back(thread{ task, id, std::span{ ranges }, ref(bins[id]) });
    }

    // No one can signal the first thread that it's all done except the main thread 
    // so we'll handle that here
    receivers[0].release();

    // theoretically the first thread should actually be the last to finish, so we'll 
    // join the threads in reverse order
    for (auto &thread : std::views::reverse(threads)) { thread.join(); }

    return bins[0];
}
}// namespace hpc
