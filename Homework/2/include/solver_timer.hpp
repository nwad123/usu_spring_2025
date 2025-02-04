#pragma once

#include "concepts.hpp"
#include "fmt/base.h"
#include "types.hpp"

namespace hpc {
template<size_t Iterations = 1>
    requires(Iterations > 0)
class SolverTimer
{
  private:
    const Config config;
    const std::span<fp> dataset;

  public:
    SolverTimer(/*in*/ const Config config, /*in*/ const std::span<fp> dataset) : config(config), dataset(dataset) {}

    template<Solver... S>
    [[nodiscard]] auto operator()(/*in*/ S &&...solvers) -> std::array<Result, sizeof...(S)>;
};

template<size_t Iterations>
    requires(Iterations > 0)
template<Solver... S>
auto SolverTimer<Iterations>::operator()(/*in*/ S &&...solvers) -> std::array<Result, sizeof...(S)>
{
    std::array<Result, sizeof...(S)> results;

    auto test = [&](/*in*/ Solver auto solver, /*in*/ const size_t index) {
        std::array<size_t, Iterations> times;

        for (auto &time : times) {
            Timer t{};
            const auto bins = solver(config, dataset);
            time = t.elapsed_ms();
        }

        const auto low = std::ranges::min(times);
        const auto high = std::ranges::max(times);
        const auto average = std::reduce(times.cbegin(), times.cend()) / times.size();

        results[index] = Result(solver.name, low, high, average, config);
    };

    size_t i{ 0 };
    (test(solvers, i++), ...);

    return results;
}
} // namespace hpc
