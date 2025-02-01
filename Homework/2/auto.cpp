#include "dataset_generator.hpp"
#include "solver_tester.hpp"
#include "solvers/parallel.hpp"
#include "solvers/serial.hpp"
#include "types.hpp"

#include <array>
#include <utility>

using namespace hpc;

auto main() -> int
{
    static constexpr std::array<size_t, 6> THREADS = { 1, 2, 4, 8, 16, 32 };
    static constexpr std::array<size_t, 6> SIZES = { 1'000'000, 10'000'000, 100'000'000, 1'000'000'000 };
    static constexpr std::pair<fp, fp> RANGE = { 0.0, 5.0 };
    static constexpr auto BINS = 5;

    // vector for storing all outputs
    std::vector<Result> results;
    results.reserve(THREADS.size() * SIZES.size());

    // handrolled cartesian product
    for (const auto threads : THREADS) {
        for (const auto size : SIZES) {
            fmt::println("LOG: testing {} threads on {} size", threads, size);
            Config config(threads, BINS, RANGE.first, RANGE.second, size);
            auto dataset = make_dataset(config);

            SolverTester solver_tester(config, dataset);

            for (const auto &result : solver_tester(Serial{}, Parallel{})) { results.emplace_back(result); }
        }
    }

    // output all of the results
    fmt::println("RESULTS:");
    fmt::println("Name,Threads,Elements,Time(ms)");
    for (const auto &result : results) {
        fmt::println("{},{},{},{}", result.name, result.config.threads, result.config.size, result.time_ms);
    }
}
