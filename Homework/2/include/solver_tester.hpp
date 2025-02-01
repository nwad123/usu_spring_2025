#pragma once

#include "concepts.hpp"
#include "fmt/base.h"
#include "types.hpp"

namespace hpc {
class SolverTester
{
  private:
    const Config config;
    const std::span<fp> dataset;

  public:
    SolverTester(/*in*/ const Config config, /*in*/ const std::span<fp> dataset) : config(config), dataset(dataset) {}

    template<Solver... S>
    [[nodiscard]] auto operator()(/*in*/ S &&...solvers) -> std::array<Result, sizeof...(S)>;
};

template<Solver... S>
auto SolverTester::operator()(/*in*/ S &&...solvers) -> std::array<Result, sizeof...(S)>
{
    std::array<Result, sizeof...(S)> results;

    auto test = [&](/*in*/ Solver auto solver, /*in*/ const size_t index) {
        Timer t{};
        const auto bins = solver(config, dataset);
        const auto elapsed = t.elapsed_ms();

        results[index] = Result(solver.name, elapsed, std::move(bins), config);
    };

    size_t i{ 0 };
    (test(solvers, i++), ...);

    return results;
}
}// namespace hpc
