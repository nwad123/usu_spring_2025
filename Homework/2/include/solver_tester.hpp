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
    auto operator()(/*in*/ S &&...solvers) -> void;
};

template<Solver... S>
auto SolverTester::operator()(/*in*/ S &&...solvers) -> void
{
    auto test = [&](/*in*/ Solver auto solver, /*in*/ const size_t index) {
        fmt::println("\"{}\": {{", solver.name);

        Timer t{};
        const auto results = solver(config, dataset);
        const auto elapsed = t.elapsed_ms();

        fmt::println("  \"Time\": {},", elapsed);

        results.report();

        if (index < sizeof...(S) - 1) {
            fmt::println("}},");
        } else {
            fmt::println("}}");
        }
    };

    fmt::println("{{");
    config.print();

    size_t solver_index{ 0 };

    ((test(solvers, solver_index++)), ...);

    fmt::println("}}");
}
}// namespace hpc
