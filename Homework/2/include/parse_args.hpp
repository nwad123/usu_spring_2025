#pragma once

#include "types.hpp"
#include <span>

namespace hpc {

namespace detail {
    using std::literals::string_view_literals::operator""sv;

    constexpr static auto USAGE = "Usage: <number of threads> <number of bins> <min> <max> <datasize>"sv;
    constexpr static auto EXPECTED_ARGC = 6U;

    auto parse_args(const std::span<char *> args) -> std::optional<Config>;
} // namespace detail

auto parse_args(const std::span<char *> args) -> std::optional<Config>;
} // namespace hpc
