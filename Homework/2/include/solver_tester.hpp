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
    auto test = [&](/*in*/ Solver auto solver) {
        fmt::println("\"{}\": {{\n  ", solver.name);
        {
            timer t{};
            const auto results = solver(config, dataset);
            const auto elapsed = t.elapsed_ms();

            fmt::println("  \"Time\": {},", elapsed);

            results.report();

            fmt::println("}},");
        }
    };

    fmt::println("{{");
    config.print();

    ((test(solvers)), ...);

    // This line is literally here because without it I can't make 
    // the JSON easily valid.
    fmt::println("\"Total tests:\": {}", sizeof...(S));
    fmt::println("}}");
}
}// namespace hpc
