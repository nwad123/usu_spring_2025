#include "concepts.hpp"
#include "dataset_generator.hpp"
#include "fmt/core.h"
#include "parse_args.hpp"
#include "solver_tester.hpp"
#include "solvers/parallel.hpp"
#include "solvers/serial.hpp"
#include "strings.hpp"
#include "types.hpp"

#include <cstdlib>
#include <optional>
#include <span>

using namespace hpc;

auto main(int argc, char **argv) -> int
{
    constexpr static auto EXPECTED_ARGC = 6U;
    const std::span<char *> args(argv, static_cast<std::size_t>(argc));

    if (args.size() != EXPECTED_ARGC) {
        fmt::println(USAGE);
        return EXIT_FAILURE;
    }

    auto config_opt = parse_args(args);

    if (!config_opt) {
        fmt::println("Failed to parse args.");
        fmt::println(USAGE);
        return EXIT_FAILURE;
    }

    const auto config = *config_opt;

    auto dataset = make_dataset(config);
    SolverTester{ config, dataset }(Serial{}, Parallel{});

    return 0;
}
