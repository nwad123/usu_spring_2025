#include "dataset_generator.hpp"
#include "solver_tester.hpp"
#include "solvers/parallel.hpp"
#include "solvers/serial.hpp"
#include "solvers/tree.hpp"
#include "types.hpp"

#include <array>
#include <utility>

using namespace hpc;

template<typename... T>
constexpr auto all_equal(const Bin &first, const T &...bins)
{
    return ((first == bins) and ...);
}

auto main() -> int
{
    static constexpr auto THREADS = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    static constexpr size_t SIZE = 10'000'000;
    static constexpr std::pair<fp, fp> RANGE = { 0.0, 5.0 };
    static constexpr auto BINS = 5;

    bool all_passed{ true };

    for (const auto THREAD : THREADS) {
        const Config config(static_cast<size_t>(THREAD), BINS, RANGE.first, RANGE.second, SIZE);
        auto dataset = make_dataset(config);

        const auto serial = Serial{}(config, dataset);
        fmt::println("  Serial");
        fmt::println("  Maxes: {}", serial.maxes);
        fmt::println("  Counts: {}", serial.counts);


        const auto parallel = Parallel{}(config, dataset);
        fmt::println("  Parallel");
        fmt::println("  Maxes: {}", parallel.maxes);
        fmt::println("  Counts: {}", parallel.counts);


        const auto tree = Tree{}(config, dataset);
        fmt::println("  Tree");
        fmt::println("  Maxes: {}", tree.maxes);
        fmt::println("  Counts: {}", tree.counts);

        if (all_equal(serial, parallel, tree)) {
            fmt::println("Outputs are equal for all implementations");
        } else {
            fmt::println("Not all outputs are equal!");
            all_passed = false;
        }
    }

    if (not all_passed) {
        fmt::println("Not all tests passed");
    }
}
