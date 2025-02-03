#pragma once

#include "concepts.hpp"
#include "types.hpp"

namespace hpc {
class Tree
{
  public:
    static constexpr std::string_view name = "Tree";
    [[nodiscard]] auto operator()(const Config &config, const std::span<fp> dataset) const -> Bin;
};
static_assert(Solver<Tree>);
}// namespace hpc
