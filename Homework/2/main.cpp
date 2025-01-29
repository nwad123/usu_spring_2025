#include "fmt/core.h"
#include <thread>
#include <span>
#include <fmt/format.h>

auto main(int argc, char **argv) -> int 
{
    constexpr static auto EXPECTED_ARGC = 5U;
    const std::span<char *> args(argv, static_cast<std::size_t>(argc));

    if (args.size() != EXPECTED_ARGC) {
        fmt::println("Usage: <number of threads> <bin count> <min meas> <max meas> <data count>");
        return EXIT_FAILURE;
    }

    return 0;
}
