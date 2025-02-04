#include "dataset_generator.hpp"
#include "fmt/core.h"
#include "parse_args.hpp"
#include "solver_runner.hpp"
#include "solvers/parallel.hpp"
#include "solvers/serial.hpp"
#include "solvers/tree.hpp"
#include "types.hpp"

#include <cstdlib>
#include <optional>
#include <span>

using namespace hpc;

/// A small command line application that calculates the histogram of 
/// the input config.
auto main(int argc, char **argv) -> int
{
    // Check args
    const std::span<char *> args(argv, static_cast<std::size_t>(argc));

    const auto config_opt = parse_args(args);
    if (not config_opt) { return EXIT_FAILURE; }

    const auto config = *config_opt;

    // Generate the histograms using each available solver
    auto dataset = make_dataset(config);
    const auto results = SolverRunner{ config, dataset }(Serial{}, Parallel{}, Tree{});

    for (const auto &result : results) {
        fmt::println("{}", std::get<0>(result));
        fmt::println("  Time:   {}ms", std::get<1>(result));
        fmt::println("  Maxes:  {}", std::get<2>(result).maxes);
        fmt::println("  Counts: {}", std::get<2>(result).counts);
    }

    return 0;
}
