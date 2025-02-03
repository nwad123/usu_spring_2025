#include "solvers/serial.hpp"

#include <algorithm>

namespace hpc {
[[nodiscard]] auto Serial::operator()(const Config &config, const std::span<fp> dataset) const -> Bin
{
    Bin bin;
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

    auto insert = [&ranges, &bin](/*in*/ const fp value) {
        auto bin_it = std::upper_bound(ranges.cbegin(), ranges.cend(), value);
        // since bin_it will be always be equal to or ahead of `ranges.begin()`
        // we can assume that this will always be positive, and therefore no
        // problem to cast it to a size_t
        auto index = static_cast<size_t>(std::distance(ranges.cbegin(), bin_it));

        bin.counts[index]++;
        if (bin.maxes[index] < value) { bin.maxes[index] = value; }
    };

    for (const auto data : dataset) { insert(data); }

    return bin;
}
}// namespace hpc
