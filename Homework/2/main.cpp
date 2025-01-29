#include "fmt/core.h"
#include <algorithm>
#include <random>
#include <span>
#include <vector>

using fp = float;

struct config
{
    size_t thread;
    size_t bins;
    fp min;
    fp max;
    size_t size;

    auto print() const -> void;
};

auto parse_args(const std::span<char *> args) -> config;
auto make_dataset(const fp min, const fp max, const size_t size) -> std::vector<fp>;

auto main(int argc, char **argv) -> int
{
    constexpr static auto EXPECTED_ARGC = 6U;
    const std::span<char *> args(argv, static_cast<std::size_t>(argc));

    if (args.size() != EXPECTED_ARGC) {
        fmt::println("Usage: <threads : nat> <bins : nat> <min : float> <max : float> <size : nat>");
        return EXIT_FAILURE;
    }

    return 0;
}

auto config::print() const -> void
{
    fmt::print(
        "Number of threads: {}\n"
        "Number of bins:    {}\n"
        "Range of dataset:  {}-{}\n"
        "Size of dataset:   {}\n",
        thread,
        bins,
        min,
        max,
        size);
}

auto make_dataset(const fp min, const fp max, const size_t size) -> std::vector<fp>
{
    constexpr static auto SEED = size_t{ 100 };
    std::mt19937 generator(SEED);
    std::uniform_real_distribution<fp> distribution(min, max);

    auto random = [&]() -> fp { return distribution(generator); };

    std::vector<fp> dataset(size, fp{ 0 });

    std::ranges::generate(dataset, random);

    return dataset;
}
