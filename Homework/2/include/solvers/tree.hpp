#pragma once

#include "concepts.hpp"
#include "types.hpp"

#include <semaphore>

namespace hpc {
class Tree
{
  public:
    static constexpr std::string_view name = "Tree";

    [[nodiscard]]
    auto operator()(const Config &config, const std::span<fp> dataset) const -> Bin;

  protected:
    struct detail
    {
        [[nodiscard]]
        static constexpr auto get_receive_list(
            /*in*/ const size_t num_threads,
            /*in*/ const size_t thread_id
        ) -> std::vector<size_t>;

        struct simple_semaphore
        {
            std::binary_semaphore sem_;

            constexpr simple_semaphore() : sem_(0) {}
            constexpr auto acquire() -> void { sem_.acquire(); }
            constexpr auto release() -> void { sem_.release(); }
        };

        struct semaphore_pair
        {
            simple_semaphore sender;
            simple_semaphore receiver;
        };

        struct ThreadSemaphores
        {
            std::vector<semaphore_pair> semaphores_;

            explicit constexpr ThreadSemaphores(/*in*/ const size_t num_threads)
                : semaphores_(std::vector<semaphore_pair>(num_threads))
            {}

            inline constexpr auto ready_to_recv_from(/*in*/ const size_t id) -> void
            {
                semaphores_[id].sender.acquire();
            }

            inline constexpr auto done_recving_from(/*in*/ const size_t id) -> void
            {
                semaphores_[id].receiver.release();
            }

            inline constexpr auto completed_work_on(/*in*/ const size_t id) -> void
            {
                semaphores_[id].sender.release();
                semaphores_[id].receiver.acquire();
            }
        };
    }; // struct detail
};
static_assert(Solver<Tree>);
} // namespace hpc


[[nodiscard]]
constexpr auto hpc::Tree::detail::get_receive_list(
    /*in*/ const size_t num_threads,
    /*in*/ const size_t thread_id
) -> std::vector<size_t>
{
    // OPTIMIZE: this whole function works fine but definitely does some extra work
    // that slows it down
    std::vector<size_t> output;

    if (thread_id == 0) {
        size_t init = 1;
        while (init < num_threads) {
            output.push_back(init);
            init <<= 1;
        }
    } else if (thread_id % 2 == 0) {
        const size_t upper_bound = [&]() {
            const size_t next_power_of_2 = std::bit_ceil(thread_id + 1);
            return std::min(num_threads, next_power_of_2);
        }();

        const size_t max_iter = [&]() {
            const size_t num_bits = 8 * sizeof(size_t);
            return std::min(num_threads - thread_id, num_bits);
        }();

        // OPTIMIZE: this for-loop is wasteful, and does many empty iterations because
        // `n` is often much greater than `config.size`
        for (size_t j = 0; j < max_iter; j++) {
            const size_t x = size_t{ 1 } << j; // if `1` is not wrapped with size_t it will quickly overflow
            const size_t n = thread_id + x;
            if (thread_id % (x * 2) == 0 and n < upper_bound) { output.push_back(n); }
        }
    }

    return output;
}
