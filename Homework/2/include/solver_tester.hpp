#pragma once

#include "concepts.hpp"
#include "types.hpp"

namespace hpc {
class SolverTester
{
  private:
    const config_t config;
    const std::span<fp> dataset;

  public:
    SolverTester(/*in*/ const config_t config, /*in*/ const std::span<fp> dataset) : config(config), dataset(dataset) {}

    template<Solver... T>
    auto operator()(/*in*/ T &&...args) -> void;
};

}// namespace hpc
