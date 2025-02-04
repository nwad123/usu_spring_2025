#pragma once

#include "types.hpp"

#include <algorithm>
#include <random>

namespace hpc {
/// Generate a random dataset of `fp` values ranging from `min` to `max` with a length of `size`.
template<std::uniform_random_bit_generator Generator>
inline auto
    make_dataset(/*in*/ const fp min, /*in*/ const fp max, /*in*/ const size_t size, /*in*/ Generator &&generator)
        -> std::vector<fp>
{
    std::uniform_real_distribution<fp> distribution(min, max);

    auto random = [&]() -> fp { return distribution(generator); };

    std::vector<fp> dataset(size, fp{ 0 });

    std::ranges::generate(dataset, random);

    return dataset;
}

// Alias of `make_dataset` that takes a config parameter for easy use.
template<size_t Seed = 100>
inline auto make_dataset(/*in*/ const Config &config) -> std::vector<fp>
{
    return make_dataset(config.min, config.max, config.size, std::mt19937{ Seed });
}
} // namespace hpc
