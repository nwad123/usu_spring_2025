#pragma once

#include "concepts.hpp"
#include "fmt/base.h"
#include "types.hpp"
#include <utility>

namespace hpc {
class SolverRunner
{
  private:
    const Config config;
    const std::span<fp> dataset;

  public:
    SolverRunner(/*in*/ const Config config, /*in*/ const std::span<fp> dataset) : config(config), dataset(dataset) {}

    template<Solver... S>
    [[nodiscard]] auto operator()(/*in*/ S &&...solvers)
        -> std::array<std::tuple<std::string_view, size_t, Bin>, sizeof...(S)>;
};

template<Solver... S>
auto SolverRunner::operator()(/*in*/ S &&...solvers)
    -> std::array<std::tuple<std::string_view, size_t, Bin>, sizeof...(S)>
{
    std::array<std::tuple<std::string_view, size_t, Bin>, sizeof...(S)> results;

    auto test = [&](/*in*/ Solver auto solver, /*in*/ const size_t index) {
        Timer t{};
        const auto bin = solver(config, dataset);
        const auto time = t.elapsed_ms();

        results[index] = { solver.name, time, std::move(bin) };
    };

    size_t i{ 0 };
    (test(solvers, i++), ...);

    return results;
}
} // namespace hpc
