#pragma once

#include "concepts.hpp"
#include "fmt/base.h"
#include "types.hpp"

namespace hpc {

/// Checks if all input bins are equal
///
/// `all_equal` returns `true` if all of the input bins are equal over `Bin.operator==`,
/// otherwise returns `false`
template<typename... /*Bin*/ T>
constexpr auto all_equal(const Bin &first, const T &...bins)
{
    return ((first == bins) and ...);
}

/// `SolverTester` objects are constructed with a given `config` and `dataset`, and then 
/// test all given solvers on that dataset, checking that the results for all given solvers 
/// are equal.
class SolverTester
{
  private:
    const Config config;
    const std::span<fp> dataset;

  public:
    /// The `dataset` span must outlive the `SolverTester` object, as the `SolverTester` does not 
    /// take ownership or copy the span.
    SolverTester(/*in*/ const Config config, /*in*/ const std::span<fp> dataset) : config(config), dataset(dataset) {}

    /// Calling `SolverTester.operator()` returns true if the outputs of all solvers is equal.
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

    // cache the first bin so that we don't test it every time
    const auto first_bin = test(first);

    return ((first_bin == test(solvers)) and ...);
}
} // namespace hpc
