#include "dataset_generator.hpp"
#include "solver_timer.hpp"
#include "solvers/parallel.hpp"
#include "solvers/serial.hpp"
#include "solvers/tree.hpp"
#include "types.hpp"

#include <array>
#include <utility>

using namespace hpc;

auto main() -> int
{
    static constexpr std::array<size_t, 6> THREADS = { 1, 2, 4, 8, 16, 32 };
    static constexpr std::array<size_t, 3> SIZES = {
        1'000'000, 10'000'000, 100'000'000, 
    };
    static constexpr std::pair<fp, fp> RANGE = { 0.0, 5.0 };
    static constexpr auto BINS = 5;

    // vector for storing all outputs
    std::vector<Result> results;
    results.reserve(THREADS.size() * SIZES.size() * 2 + SIZES.size());

    // Single pass for serial timing
    for (const auto size : SIZES) {
        Config config(1, BINS, RANGE.first, RANGE.second, size);
        auto dataset = make_dataset(config);

        SolverTimer solver_tester(config, dataset);

        for (const auto &result : solver_tester(Serial{})) { results.emplace_back(result); }
    }

    // handrolled cartesian product for parallel options
    for (const auto threads : THREADS) {
        for (const auto size : SIZES) {
            Config config(threads, BINS, RANGE.first, RANGE.second, size);
            auto dataset = make_dataset(config);

            SolverTimer solver_tester(config, dataset);

            for (const auto &result : solver_tester(Parallel{}, Tree{})) { results.emplace_back(result); }
        }
    }

    // output all of the results
    fmt::println("Name,Threads,Elements,Time(ms)");
    for (const auto &result : results) {
        fmt::println("{},{},{},{}", result.name, result.config.threads, result.config.size, result.time_ms);
    }
}
