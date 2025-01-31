#pragma once

#include "types.hpp"
#include <span>

namespace hpc {

template<typename S>
concept Solver = requires(const S &solver, const config_t &config, const std::span<fp> dataset) {
    { solver.operator()(config, dataset) } -> std::same_as<bin_results_t>;
};
}// namespace hpc
