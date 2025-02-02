#pragma once

#include "concepts.hpp"
#include "types.hpp"

namespace hpc {
class StaticParallel
{
  public:
    static constexpr std::string_view name = "Static Parallel";
    template<Config config>
    [[nodiscard]] auto operator()(const std::span<fp> dataset) const -> Bin;
};
static_assert(StaticSolver<StaticParallel>);
}// namespace hpc
