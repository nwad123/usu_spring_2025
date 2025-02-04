#include "dataset_generator.hpp"
#include "solver_tester.hpp"
#include "solvers/parallel.hpp"
#include "solvers/serial.hpp"
#include "solvers/tree.hpp"
#include "types.hpp"

#include <random>
#include <utility>

using namespace hpc;

/// Tests that outputs from each solver are equal for all combinations of 
/// `THREADS` and `SIZES`
auto main() -> int
{
    // constants
    static constexpr auto THREADS = { 1, 2, 3, 4, 8, 16, 32, 64 };
    static constexpr auto SIZES = { 0, 16, 200, 100, 279, 592, 10'000'000 };
    static constexpr std::pair<fp, fp> RANGE = { 0.0, 5.0 };
    static constexpr auto BINS = 5;

    // id for tests
    size_t test_id{ 0 };

    // handrolled cartesian product for all different configurations
    for (const auto SIZE : SIZES) {
        const auto size = static_cast<size_t>(SIZE);

        fmt::println("\nGenerating dataset with {} values", size);
        auto dataset = make_dataset(RANGE.first, RANGE.second, size, std::mt19937{ 100 });

        for (const auto THREAD : THREADS) {
            const auto thread = static_cast<size_t>(THREAD);

            const Config config(thread, BINS, RANGE.first, RANGE.second, dataset.size());
            const auto solver_tester = SolverTester(config, dataset);

            if (not solver_tester(Serial{}, Parallel{}, Tree{})) {
                fmt::println("\nFailed test {} with parameters:", test_id);
                config.print();
                break;
            } else {
                fmt::println("  Passed test {} with {} threads", test_id, thread);
            }

            test_id++;
        }
    }
}
