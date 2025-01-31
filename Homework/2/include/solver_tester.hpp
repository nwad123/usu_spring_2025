#pragma once

#include "concepts.hpp"
#include "fmt/base.h"
#include "types.hpp"

namespace hpc {
class SolverTester
{
  private:
    const config_t config;
    const std::span<fp> dataset;

  public:
    SolverTester(/*in*/ const config_t config, /*in*/ const std::span<fp> dataset) : config(config), dataset(dataset) {}

    template<Solver... S>
    auto operator()(/*in*/ S &&...solvers) -> void;
};

template<Solver... S>
auto SolverTester::operator()(/*in*/ S &&...solvers) -> void
{
    auto test = [&](Solver auto solver) {
        fmt::println("# Testing: {}", solver.name);
        {
            timer t{};
            const auto results = solver(config, dataset);
            const auto elapsed = t.elapsed_ms();

            fmt::println("# Finished. Took {} ms", elapsed);

            results.report();

            fmt::println("");
        }
    };

    ((test(solvers)), ...);
}
}// namespace hpc
