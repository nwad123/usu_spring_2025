#include "concepts.hpp"
#include "fmt/core.h"
#include "parse_args.hpp"
#include "strings.hpp"
#include "types.hpp"
#include "dataset_generator.hpp"

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

    auto config = parse_args(args);

    if (!config) {
        fmt::println("Failed to parse args.");
        fmt::println(USAGE);
        return EXIT_FAILURE;
    }

    fmt::println(WELCOME);
    config->print();

    auto dataset = make_dataset(*config);

    return 0;
}
