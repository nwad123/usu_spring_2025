#pragma once

#include "concepts.hpp"
#include "fmt/base.h"
#include "types.hpp"
#include <cmath>

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
        std::array<double, Iterations> times;

        for (auto &time : times) {
            Timer t{};
            const auto bins = solver(config, dataset);
            time = t.elapsed_ms();
        }

        const auto average = std::reduce(times.cbegin(), times.cend()) / double{ times.size() };
        const auto variance =
            std::reduce(times.cbegin(), times.cend(), double{ 0 }, [&average](double accumulator, const double &val) {
                return accumulator + (((val - average) * (val - average)) / std::max(double{ Iterations - 1 }, 1.0));
            });
        const auto std_dev = std::sqrt(variance);
        const auto [min, max] = std::ranges::minmax(times);

        results[index] = Result(solver.name, average, std_dev, min, max, config);
    };

    size_t i{ 0 };
    (test(solvers, i++), ...);

    return results;
}
} // namespace hpc
