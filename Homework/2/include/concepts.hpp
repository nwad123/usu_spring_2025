#pragma once

#include "types.hpp"
#include <span>

namespace hpc {

template<typename S>
concept Named = requires() {
    { S::name } -> std::convertible_to<std::string_view>;
};

template<typename S>
concept Solver = requires(const S &solver, const Config &config, const std::span<fp> dataset) {
    { solver.operator()(config, dataset) } -> std::same_as<Bin>;
} && Named<S>;

template<typename S, Config config = Config{}>
concept StaticSolver = requires(const S &solver, const std::span<fp> dataset) {
    { solver.template operator()<config>(dataset) } -> std::same_as<Bin>;
} && Named<S>;

}// namespace hpc
