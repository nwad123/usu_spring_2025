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
    // constants
    static constexpr auto THREADS = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    static constexpr auto SIZES = { 10'000'000, 100'000'000, 1'000'000'000 };
    static constexpr std::pair<fp, fp> RANGE = { 0.0, 5.0 };
    static constexpr auto BINS = 5;

    // id for tests
    size_t test_id{ 0 };

    // handrolled cartesian product for different configurations
    for (const auto SIZE : SIZES) {
        const auto size = static_cast<size_t>(SIZE);

        fmt::println("Generating dataset with {} values", size);
        auto dataset = make_dataset(RANGE.first, RANGE.second, size, std::mt19937{ 100 });

        for (const auto THREAD : THREADS) {
            const auto thread = static_cast<size_t>(THREAD);

            const Config config(thread, BINS, RANGE.first, RANGE.second, dataset.size());
            const auto solver_tester = SolverTester(config, dataset);

            if (not solver_tester(Serial{}, Parallel{}, Tree{})) {
                fmt::println("Failed test {} with parameters:", test_id);
                config.print();
                break;
            } else {
                fmt::println("Passed test {} with {} threads", test_id, thread);
            }

            test_id++;
        }
    }
}
