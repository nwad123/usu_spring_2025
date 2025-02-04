#pragma once

#include "concepts.hpp"
#include "fmt/base.h"
#include "types.hpp"
#include <utility>

namespace hpc {

/// `SolverRunner` objects are constructed with a given `config` and `dataset`, and then can 
/// "run" any given solver on that dataset, both generating results and timing the execution 
/// of the solver.
class SolverRunner
{
  private:
    const Config config;
    const std::span<fp> dataset;

  public:
    /// The `dataset` span must outlive the `SolverRunner` object, as the `SolverRunner` does not 
    /// take ownership or copy the span.
    SolverRunner(/*in*/ const Config config, /*in*/ const std::span<fp> dataset) : config(config), dataset(dataset) {}

    /// Calling `SolverRunner.operator()` on any number of solvers produces and an array of tuples 
    /// of the following form: <Name, Execution Time (ms), Bins>
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
