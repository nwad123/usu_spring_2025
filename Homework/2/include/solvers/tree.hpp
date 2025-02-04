#pragma once

#include "concepts.hpp"
#include "types.hpp"

#include <semaphore>

namespace hpc {
class Tree
{
  public:
    static constexpr std::string_view name = "Tree";
    [[nodiscard]] auto operator()(const Config &config, const std::span<fp> dataset) const -> Bin;

  protected:
    struct detail
    {
        [[nodiscard]]
        static constexpr auto get_receive_list(
            /*in*/ const size_t num_threads,
            /*in*/ const size_t thread_id
        ) -> std::vector<size_t>;

        [[nodiscard]] static constexpr auto get_bin_ranges(
            /*in*/ const size_t num_bins,
            /*in*/ const std::pair<fp, fp> range
        ) -> std::vector<fp>;

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

            inline constexpr auto completed_work(/*in*/ const size_t id) -> void
            {
                semaphores_[id].sender.release();
                semaphores_[id].receiver.acquire();
            }
        };
    }; // struct detail
};
static_assert(Solver<Tree>);
} // namespace hpc

/* ### Implementations ### */ 

