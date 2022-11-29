#pragma once

template <auto val>
struct CT {
    static constexpr auto value{val};
};

template <auto val>
constexpr CT<val> ct{};