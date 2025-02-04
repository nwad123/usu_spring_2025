#pragma once

#include "concepts.hpp"
#include "types.hpp"

namespace hpc {
/// The `Serial` solver implements a single threaded approach to generating a histogram. This
/// approach is slower than the parallel implementations, but was used as a reference point
/// both for correctness and timing.
class Serial
{
  public:
    static constexpr std::string_view name = "SerialSum";
    /// `Serial.operator()` generates the histogram bins based of the config and input dataset.
    /// Note that the data under the `dataset` span must outlive the `Serial` object as no
    /// attempt to copy or take ownership of the data is made.
    [[nodiscard]] auto operator()(const Config &config, const std::span<fp> dataset) const -> Bin;
};

// The `Serial` class must satisfy the `Solver` concept
static_assert(Solver<Serial>);

} // namespace hpc
