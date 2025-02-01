#include "parse_args.hpp"

#include "fmt/base.h"
#include <charconv>

auto hpc::parse_args(const std::span<char *> args) -> std::optional<Config>
{
    if (args.size() != detail::EXPECTED_ARGC) {
        fmt::println(detail::USAGE);
        return std::nullopt;
    }

    const auto config = detail::parse_args(args);

    if (!config) {
        fmt::println("Failed to parse args.");
        fmt::println(detail::USAGE);
        return std::nullopt;
    }

    return config;
}

auto hpc::detail::parse_args(const std::span<char *> args) -> std::optional<Config>
{
    auto parse_int = [](const char *str, size_t &number) -> bool {
        const auto len = strlen(str);
        const auto [_, ec] = std::from_chars(str, str + len, number);

        return ec == std::errc();
    };

    auto parse_float = [](const char *str, fp &number) -> bool {
        char *c{};
        long double ld = strtold(str, &c);
        number = static_cast<fp>(ld);
        return (c != str);
    };

    Config c{};

    constexpr static auto THREAD_INDEX = 1UL;
    constexpr static auto BINS_INDEX = 2UL;
    constexpr static auto MIN_INDEX = 3UL;
    constexpr static auto MAX_INDEX = 4UL;
    constexpr static auto DATA_INDEX = 5UL;

    if (!parse_int(args[THREAD_INDEX], c.threads)) {
        fmt::println("Failed to get number of threads.");
        return std::nullopt;
    }

    if (!parse_int(args[BINS_INDEX], c.bins)) {
        fmt::println("Failed to get number of bins.");
        return std::nullopt;
    }

    if (!parse_float(args[MIN_INDEX], c.min)) {
        fmt::println("Failed to get minimum range for dataset.");
        return std::nullopt;
    }

    if (!parse_float(args[MAX_INDEX], c.max)) {
        fmt::println("Failed to get maximum range for dataset.");
        return std::nullopt;
    }

    if (!parse_int(args[DATA_INDEX], c.size)) {
        fmt::println("Failed to get number of points in the dataset.");
        return std::nullopt;
    }

    return c;
}
