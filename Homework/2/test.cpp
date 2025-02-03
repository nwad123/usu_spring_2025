#include "dataset_generator.hpp"
#include "solver_tester.hpp"
#include "solvers/parallel.hpp"
#include "solvers/serial.hpp"
#include "solvers/tree.hpp"
#include "types.hpp"

#include <array>
#include <utility>

using namespace hpc;

auto main() -> int
{
    static constexpr size_t THREADS = 2;
    static constexpr size_t SIZE = 10'000'000;
    static constexpr std::pair<fp, fp> RANGE = { 0.0, 5.0 };
    static constexpr auto BINS = 5;

    const Config config(THREADS, BINS, RANGE.first, RANGE.second, SIZE);
    auto dataset = make_dataset(config);

    const auto serial = Serial{}(config, dataset);
    fmt::println("Serial");
    fmt::println("Maxes: {}", serial.maxes);
    fmt::println("Counts: {}", serial.counts);


    const auto parallel = Parallel{}(config, dataset);
    fmt::println("Parallel");
    fmt::println("Maxes: {}", parallel.maxes);
    fmt::println("Counts: {}", parallel.counts);


    const auto tree = Tree{}(config, dataset);
    fmt::println("Tree");
    fmt::println("Maxes: {}", tree.maxes);
    fmt::println("Counts: {}", tree.counts);
}
