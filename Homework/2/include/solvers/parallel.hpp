#pragma once

#include "concepts.hpp"
#include "types.hpp"

namespace hpc {
class Parallel
{
  public:
    static constexpr std::string_view name = "GlobalSum";
    [[nodiscard]] auto operator()(const Config &config, const std::span<fp> dataset) const -> Bin;
};
static_assert(Solver<Parallel>);
}// namespace hpc
