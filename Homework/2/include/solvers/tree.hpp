#pragma once

#include "concepts.hpp"
#include "types.hpp"

#include <semaphore>

namespace hpc {
/// The `Tree` solver implements a multithreaded Tree Structured Sum approach to generating a
/// histogram.
class Tree
{
  public:
    static constexpr std::string_view name = "TreeStructuredSum";

    /// `Tree.operator()` generates the histogram bins based of the config and input dataset.
    /// Note that the data under the `dataset` span must outlive the `Tree` object as no
    /// attempt to copy or take ownership of the data is made.
    [[nodiscard]]
    auto operator()(const Config &config, const std::span<fp> dataset) const -> Bin;

  protected:
    /// The `Tree` class has a `detail` subclass that abstracts away some parts of the histogram
    /// algorithm. This is to provide more readable code, and as often as possible functions are
    /// marked inline, constexpr, or both in order to assure that high performance can still
    /// be achieved.
    struct detail
    {
        /// The Tree Structured sum approach works by merging the work done by the different
        /// threads together in a tree-like manner across threads. For example, if you had
        /// four threads then thread 1 would be in charge of merging the work of thread 2 and
        /// thread 3 together, and thread 3 would be in charge of merging the work of thread
        /// 4. See the example below:
        /*
         * Threads: 1  2  3  4
         *          | /   | /
         *          +     +
         *          |    /
         *          |  /
         *          +
         *          <Final result in thread 1>
         */
        /// Each thread needs to know what threads it can receive from, and it also need to know
        /// when it's done being used. This function provides a static way of determining what
        /// threads a thread can recieve from.
        ///
        /// `num_threads` is the total number of threads. Must be > 0
        /// `thread_id` is the id of the thread that the recieve list is to be generated for.
        ///     0 < `thread_id` < `num_threads`
        [[nodiscard]]
        static constexpr auto get_receive_list(
            /*in*/ const size_t num_threads,
            /*in*/ const size_t thread_id
        ) -> std::vector<size_t>;

        /// C++ semaphores can't be default constructed, so I wrote a wrapper class to default
        /// construct them.
        struct simple_semaphore
        {
            std::binary_semaphore sem_;

            constexpr simple_semaphore() : sem_(0) {}
            constexpr auto acquire() -> void { sem_.acquire(); }
            constexpr auto release() -> void { sem_.release(); }
        };

        // For each thread we'll need a "send" and "recieve" semaphore to synchronize the passing
        // of bins between threads. Prior to this struct I implemented this as a pair of vectors,
        // one for sending and one for receiving. However I noticed that when a reciever semaphore
        // is accessed the sender semaphore is soon accessed and vice versa, so it makes sense to
        // them local to each other in memory.
        struct semaphore_pair
        {
            simple_semaphore sender;
            simple_semaphore receiver;
        };

        /// `ThreadSemaphores` provides a simple abstraction for the actions that each thread can
        /// take in the `Tree` class. The names of the methods are self-explanatory.
        struct ThreadSemaphores
        {
            std::vector<semaphore_pair> semaphores_;

            explicit constexpr ThreadSemaphores(/*in*/ const size_t num_threads)
                : semaphores_(std::vector<semaphore_pair>(num_threads))
            {}

            /// Indicates that the caller thread is ready to receive bins from thread `id`
            inline constexpr auto ready_to_recv_from(/*in*/ const size_t id) -> void
            {
                semaphores_[id].sender.acquire();
            }

            /// Indicates that the caller thread is done receiving bins from thread `id`, which
            /// indicates to thread `id` that they can close.
            inline constexpr auto done_recving_from(/*in*/ const size_t id) -> void
            {
                semaphores_[id].receiver.release();
            }

            /// Indicates that all work has be completed on thread `id` and that it's ready
            /// to be consumed.
            inline constexpr auto completed_work_on(/*in*/ const size_t id) -> void
            {
                semaphores_[id].sender.release();
                semaphores_[id].receiver.acquire();
            }
        };
    }; // struct detail
};

// `Tree` must satisfy the `Solver` concept
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

    // For `id == 0` we just need to get all threads that are power of 2
    if (thread_id == 0) {
        size_t init = 1;
        while (init < num_threads) {
            output.push_back(init);
            init <<= 1;
        }
    } 
    // We don't need to assign any recieves to odd threads, so we only check for 
    // even `id` threads now.
    else if (thread_id % 2 == 0) {
        // The upper bound of possible threads to receieve from
        const size_t upper_bound = [&]() {
            const size_t next_power_of_2 = std::bit_ceil(thread_id + 1);
            return std::min(num_threads, next_power_of_2);
        }();

        // This is a conservative upperbound on which threads to check
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
