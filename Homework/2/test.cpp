#include "dataset_generator.hpp"
#include "solver_tester.hpp"
#include "solvers/parallel.hpp"
#include "solvers/serial.hpp"
#include "solvers/tree.hpp"
#include "types.hpp"

#include <random>
#include <utility>

using namespace hpc;

auto main() -> int
{
    static constexpr auto THREADS = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    static constexpr size_t SIZE = 10'000'000;
    static constexpr std::pair<fp, fp> RANGE = { 0.0, 5.0 };
    static constexpr auto BINS = 5;

    auto dataset = make_dataset(RANGE.first, RANGE.second, SIZE, std::mt19937{ 100 });

    for (const auto THREAD : THREADS) {
        const Config config(static_cast<size_t>(THREAD), BINS, RANGE.first, RANGE.second, dataset.size());

        const auto solver_tester = SolverTester(config, dataset);

        if (not solver_tester(Serial{}, Parallel{}, Tree{})) {
            fmt::println("Failed with parameters:");
            config.print();
            break;
        } else {
            fmt::println("Passed");
        }
    }
}
