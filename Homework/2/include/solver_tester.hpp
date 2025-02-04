#pragma once

#include "concepts.hpp"
#include "fmt/base.h"
#include "types.hpp"

namespace hpc {
template<typename... T>
/// Requires all T to be `Bin`
constexpr auto all_equal(const Bin &first, const T &...bins)
{
    return ((first == bins) and ...);
}

class SolverTester
{
  private:
    const Config config;
    const std::span<fp> dataset;

  public:
    SolverTester(/*in*/ const Config config, /*in*/ const std::span<fp> dataset) : config(config), dataset(dataset) {}

    template<Solver S, Solver... Ss>
    [[nodiscard]] auto operator()(/*in*/ S &&first, /*in*/ Ss &&...solvers) const -> bool;
};

template<Solver S, Solver... Ss>
auto SolverTester::operator()(/*in*/ S &&first, /*in*/ Ss &&...solvers) const -> bool
{
    auto test = [&](/*in*/ Solver auto solver) {
        const auto bins = solver(config, dataset);
        return bins;
    };

    return ((test(first) == test(solvers)) and ...);
}
} // namespace hpc
