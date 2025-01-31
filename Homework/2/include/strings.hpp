#pragma once

#include <string_view>

namespace hpc {

using std::literals::string_view_literals::operator""sv;

constexpr static auto USAGE = "Usage: <threads : nat> <bins : nat> <min : float> <max : float> <size : nat>"sv;
constexpr static auto WELCOME =
    "---- Homework 2 - Histogram -----\n"
    "          Nick Waddoups\n"sv;

}// namespace hpp
