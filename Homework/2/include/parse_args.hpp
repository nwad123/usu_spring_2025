#pragma once

#include "types.hpp"
#include <span>

namespace hpc {

namespace detail {
    using std::literals::string_view_literals::operator""sv;

    constexpr static auto USAGE = "Usage: <threads : nat> <bins : nat> <min : float> <max : float> <size : nat>"sv;
    constexpr static auto EXPECTED_ARGC = 6U;

    auto parse_args(const std::span<char *> args) -> std::optional<config_t>;
}// namespace detail

auto parse_args(const std::span<char *> args) -> std::optional<config_t>;
}// namespace hpc
