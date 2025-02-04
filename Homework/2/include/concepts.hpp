#pragma once

#include "types.hpp"
#include <span>

namespace hpc {

template<typename S>
concept Named = requires() {
    { S::name } -> std::convertible_to<std::string_view>;
};

/// A `Solver` is what I named the objects that produce the histogram bins.
///
/// `Solver`s are required to define `operator()` that takes in a 
/// config and dataset parameter.
/// Although not captured in the concept, semantically speaking differ `Solver` objects 
/// of the same type should not exhibit different behavior.
template<typename S>
concept Solver = requires(const S &solver, const Config &config, const std::span<fp> dataset) {
    { solver.operator()(config, dataset) } -> std::same_as<Bin>;
} && Named<S>;

/// A `StaticSolver` should exhibit similar behavior to a normal `Solver`, but takes the config 
/// as a template parameter instead.
template<typename S, Config config = Config{}>
concept StaticSolver = requires(const S &solver, const std::span<fp> dataset) {
    { solver.template operator()<config>(dataset) } -> std::same_as<Bin>;
} && Named<S>;

}// namespace hpc
