#pragma once

#include "concepts.hpp"
#include "types.hpp"

namespace hpc {
class Parallel
{
  public:
    [[nodiscard]] auto operator()(const config_t &config, const std::span<fp> dataset) const -> bin_results_t;
};
static_assert(Solver<Parallel>);
}// namespace hpc
