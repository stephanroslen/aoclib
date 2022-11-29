#pragma once

#include <array>
#include <climits>
#include <cstddef>

template <typename T>
struct Coord2D {
    struct Hasher {
        constexpr size_t operator()(const Coord2D& val) const noexcept
        {
            const size_t tx{static_cast<size_t>(val.x)};
            const size_t ty{static_cast<size_t>(val.y)};
            return tx ^ (ty << ((sizeof(size_t) * CHAR_BIT) / 2)) ^ (ty >> ((sizeof(size_t) * CHAR_BIT) / 2));
        }
    };

    T x;
    T y;

    constexpr Coord2D& operator+=(const Coord2D& other) noexcept
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    constexpr Coord2D operator+(const Coord2D& other) const noexcept
    {
        Coord2D tmp{*this};
        tmp += other;
        return tmp;
    }

    constexpr Coord2D operator-() const noexcept
    {
        return {-x, -y};
    }

    constexpr Coord2D& operator-=(const Coord2D& other) noexcept
    {
        return *this += -other;
    }

    constexpr Coord2D operator-(const Coord2D& other) const noexcept
    {
        return *this + -other;
    }

    constexpr auto operator<=>(const Coord2D& other) const noexcept = default;

    constexpr bool isInRectangle(const Coord2D& topLeft, const Coord2D& bottomRight) const noexcept
    {
        return x >= topLeft.x && y >= topLeft.y && x <= bottomRight.x && y <= bottomRight.y;
    }

    static consteval std::array<Coord2D, 4> adjacencies() noexcept
        requires(std::is_signed_v<T>)
    {
        return {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};
    }

    static consteval std::array<Coord2D, 8> adjacenciesDiag() noexcept
        requires(std::is_signed_v<T>)
    {
        return {{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}};
    }
};
