#pragma once

#include "concepts.hpp"
#include "types.hpp"

namespace hpc {
class Serial
{
  public:
    static constexpr std::string_view name = "SerialSum";
    [[nodiscard]] auto operator()(const Config &config, const std::span<fp> dataset) const -> Bin;
};
static_assert(Solver<Serial>);
}// namespace hpc
