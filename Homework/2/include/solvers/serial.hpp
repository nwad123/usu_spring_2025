#pragma once

#include "concepts.hpp"
#include "types.hpp"

namespace hpc {
class Serial
{
  public:
    static constexpr std::string_view name = "Parallel";
    [[nodiscard]] auto operator()(const config_t &config, const std::span<fp> dataset) const -> bin_results_t;
};
static_assert(Solver<Serial>);
}// namespace hpc
