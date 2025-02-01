#pragma once

#include "types.hpp"

#include <algorithm>
#include <random>

namespace hpc {
inline auto make_dataset(const Config &config) -> std::vector<fp>
{
    constexpr static auto SEED = size_t{ 100 };
    std::mt19937 generator(SEED);
    std::uniform_real_distribution<fp> distribution(config.min, config.max);

    auto random = [&]() -> fp { return distribution(generator); };

    std::vector<fp> dataset(config.size, fp{ 0 });

    std::ranges::generate(dataset, random);

    return dataset;
}
}// namespace hpc
