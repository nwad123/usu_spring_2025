#include "concepts.hpp"
#include "dataset_generator.hpp"
#include "fmt/core.h"
#include "parse_args.hpp"
#include "solver_timer.hpp"
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
    const std::span<char *> args(argv, static_cast<std::size_t>(argc));

    const auto config_opt = parse_args(args);
    const auto config = *config_opt;

    auto dataset = make_dataset(config);
    const auto results = SolverTimer{ config, dataset }(Serial{}, Parallel{});

    fmt::println("Name,Threads,Elements,Time(ms)");
    for (const auto &result : results) {
        fmt::println("{},{},{},{}", result.name, result.config.threads, result.config.size, result.time_ms);
    }

    return 0;
}
