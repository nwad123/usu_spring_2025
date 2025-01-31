#include "fmt/core.h"
#include "fmt/ranges.h"
#include <algorithm>
#include <charconv>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <optional>
#include <random>
#include <span>
#include <string_view>
#include <thread>
#include <vector>

using std::literals::string_view_literals::operator""sv;
using fp = float;

constexpr static auto USAGE = "Usage: <threads : nat> <bins : nat> <min : float> <max : float> <size : nat>"sv;
constexpr static auto WELCOME =
    "---- Homework 2 - Histogram -----\n"
    "          Nick Waddoups\n"sv;
constexpr static auto CONFIG = "Configuration"sv;

struct config_t
{
    size_t threads;
    size_t bins;
    fp min;
    fp max;
    size_t size;

    auto print() const -> void;
};

struct bin_results_t
{
    std::vector<fp> maxes;
    std::vector<size_t> counts;

    auto report() const -> void;
};

auto parse_args(const std::span<char *> args) -> std::optional<config_t>;

auto make_dataset(const config_t &config) -> std::vector<fp>;

auto serial_solver(const config_t &config, const std::span<fp> dataset) -> bin_results_t;
auto tree_solver(const config_t &config, const std::span<fp> dataset) -> bin_results_t;
auto std_solver(const config_t &config, const std::span<fp> dataset) -> bin_results_t;

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
    fmt::println(CONFIG);
    config->print();

    auto dataset = make_dataset(*config);

    {
        auto bins = serial_solver(*config, dataset);
        bins.report();
    }

    {
        auto tree_bins = tree_solver(*config, dataset);
        tree_bins.report();
    }

    return 0;
}

auto config_t::print() const -> void
{
    fmt::print(
        "Number of threads: {}\n"
        "Number of bins:    {}\n"
        "Range of dataset:  {}-{}\n"
        "Size of dataset:   {}\n",
        threads,
        bins,
        min,
        max,
        size);
}

auto bin_results_t::report() const -> void
{
    fmt::println("bin_maxes:  {}", maxes);
    fmt::println("bin_counts: {}", counts);
}

auto parse_args(const std::span<char *> args) -> std::optional<config_t>
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

    config_t c{};

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
auto make_dataset(const config_t &config) -> std::vector<fp>
{
    constexpr static auto SEED = size_t{ 100 };
    std::mt19937 generator(SEED);
    std::uniform_real_distribution<fp> distribution(config.min, config.max);

    auto random = [&]() -> fp { return distribution(generator); };

    std::vector<fp> dataset(config.size, fp{ 0 });

    std::ranges::generate(dataset, random);

    return dataset;
}

auto serial_solver(const config_t &config, const std::span<fp> dataset) -> bin_results_t
{
    bin_results_t bin;
    bin.maxes.resize(config.bins);
    bin.counts.resize(config.bins);

    std::vector<fp> ranges(config.bins);
    fp f{ config.max };
    fp diff{ (config.max - config.min) / static_cast<fp>(config.bins) };

    for (auto it = ranges.rbegin(); it != ranges.rend(); ++it) {
        auto &range = *it;
        range = f;
        f -= diff;
    }

    auto insert = [&ranges, &bin](const fp value) {
        auto bin_it = std::upper_bound(ranges.cbegin(), ranges.cend(), value);
        auto index = std::distance(ranges.cbegin(), bin_it);

        bin.counts[index]++;
        if (bin.maxes[index] < value) { bin.maxes[index] = value; }
    };

    for (const auto data : dataset) { insert(data); }

    return bin;
}

auto tree_solver(const config_t &config, const std::span<fp> dataset) -> bin_results_t
{
    using std::thread;
    using std::ref;

    auto task = [&config, &dataset](/*in*/ size_t id, /*out*/ bin_results_t &bin) {
        const auto num_elements = config.size / config.threads;
        const auto starting_element = id * num_elements;

        const auto dataset_slice = dataset.subspan(starting_element, num_elements);

        bin.maxes.resize(config.bins);
        bin.counts.resize(config.bins);

        std::vector<fp> ranges(config.bins);
        fp f{ config.max };
        fp diff{ (config.max - config.min) / static_cast<fp>(config.bins) };

        for (auto it = ranges.rbegin(); it != ranges.rend(); ++it) {
            auto &range = *it;
            range = f;
            f -= diff;
        }

        auto insert = [&ranges, &bin](const fp value) {
            auto bin_it = std::upper_bound(ranges.cbegin(), ranges.cend(), value);
            auto index = std::distance(ranges.cbegin(), bin_it);

            bin.counts[index]++;
            if (bin.maxes[index] < value) { bin.maxes[index] = value; }
        };

        for (const auto data : dataset_slice) { insert(data); }
    };


    std::vector<bin_results_t> bins{ config.threads };
    std::vector<thread> threads{};
    threads.reserve(config.threads);

    for (size_t id = 0; id < config.threads; id++) { threads.push_back(thread{ task, id, ref(bins[id]) }); }

    for (auto &thread : threads) { thread.join(); }

    bin_results_t output{};
    output.maxes.resize(config.bins);
    output.counts.resize(config.bins);

    for (auto &bin : bins) {
        for (size_t i = 0; i < config.bins; i++) {
            output.maxes[i] = std::max(bin.maxes[i], output.maxes[i]);
            output.counts[i] += bin.counts[i];
        }
    }

    return output;
}
