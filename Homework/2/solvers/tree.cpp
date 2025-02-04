#include "solvers/tree.hpp"
#include "solvers/detail/bin_limits.hpp"

#include <algorithm>
#include <bit>
#include <ranges>
#include <thread>

namespace hpc {

[[nodiscard]]
auto Tree::operator()(const Config &config, const std::span<fp> dataset) const -> Bin
{
    using std::thread;
    using std::ref;

    auto bin_steps = hpc::detail::get_bin_steps(config.bins, { config.min, config.max });
    auto semaphores = detail::ThreadSemaphores(config.threads);
    auto bins = std::vector<Bin>{ config.threads };

    auto task = [&config, &dataset, &semaphores, &bins](
                    /*in*/ size_t id, /*in*/ const std::span<fp> ranges, /*out*/ Bin &bin
                ) -> void {
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
            // since bin_it will be always be equal to or ahead of `ranges.begin()`
            // we can assume that this will always be positive, and therefore no
            // problem to cast it to a size_t
            auto index = static_cast<size_t>(std::distance(ranges.begin(), bin_it));

            bin.counts[index]++;
            if (bin.maxes[index] < value) { bin.maxes[index] = value; }
        };

        for (const auto data : dataset_slice) { insert(data); }

        // Receiving all the data
        const auto recv_list = detail::get_receive_list(config.threads, id);

        for (const auto recv_id : recv_list) {
            semaphores.ready_to_recv_from(recv_id);

            const auto &recv_bin = bins[recv_id];

            for (size_t i = 0; i < config.bins; i++) {
                bin.maxes[i] = std::max(bin.maxes[i], recv_bin.maxes[i]);
                bin.counts[i] += recv_bin.counts[i];
            }

            semaphores.done_recving_from(recv_id);
        }

        semaphores.completed_work_on(id);
        return;
    };

    std::vector<thread> threads{};
    threads.reserve(config.threads);

    for (size_t id = 0; id < config.threads; id++) {
        threads.push_back(thread{ task, id, std::span{ bin_steps }, ref(bins[id]) });
    }

    // No one can signal the first thread that it's all done except the main thread
    // so we'll handle that here
    semaphores.semaphores_[0].receiver.release();

    // theoretically the first thread should actually be the last to finish, so we'll
    // join the threads in reverse order
    for (auto &thread : std::views::reverse(threads)) { thread.join(); }

    return bins[0];
}
} // namespace hpc
