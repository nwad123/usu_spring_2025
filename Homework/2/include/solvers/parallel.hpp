#pragma once

#include "concepts.hpp"
#include "types.hpp"

namespace hpc {
/// The `Parallel` solver implements a multithreaded Global Sum approach to generating a histogram.
class Parallel
{
  public:
    static constexpr std::string_view name = "GlobalSum";
    /// `Parallel.operator()` generates the histogram bins based of the config and input dataset.
    /// Note that the data under the `dataset` span must outlive the `Parallel` object as no
    /// attempt to copy or take ownership of the data is made.
    [[nodiscard]] auto operator()(const Config &config, const std::span<fp> dataset) const -> Bin;
};

// The `Parallel` class must satisfy the `Solver` concept.
static_assert(Solver<Parallel>);

} // namespace hpc
