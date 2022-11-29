#pragma once

#include <array>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <tuple>

template <typename T>
struct Coord3D {
    struct Hasher {
        constexpr size_t operator()(const Coord3D& val) const noexcept
        {
            const size_t tx{static_cast<size_t>(val.x)};
            const size_t ty{static_cast<size_t>(val.y)};
            const size_t tz{static_cast<size_t>(val.z)};
            return tx ^ (ty << ((sizeof(size_t) * CHAR_BIT) / 4)) ^ (ty >> ((sizeof(size_t) * CHAR_BIT) / 4 * 3))
                   ^ (tz << ((sizeof(size_t) * CHAR_BIT) / 2)) ^ (tz >> ((sizeof(size_t) * CHAR_BIT) / 2));
        }
    };

    T x;
    T y;
    T z;

    constexpr Coord3D& operator+=(const Coord3D& other) noexcept
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    constexpr Coord3D operator+(const Coord3D& other) const noexcept
    {
        Coord3D tmp{*this};
        tmp += other;
        return tmp;
    }

    constexpr Coord3D operator-() const noexcept
    {
        return {-x, -y, -z};
    }

    constexpr Coord3D& operator-=(const Coord3D& other) noexcept
    {
        return *this += -other;
    }

    constexpr Coord3D operator-(const Coord3D& other) const noexcept
    {
        return *this + -other;
    }

    constexpr auto operator<=>(const Coord3D& other) const noexcept = default;

    constexpr bool isInCuboid(const Coord3D& topLeft, const Coord3D& bottomRight) const noexcept
    {
        return x >= topLeft.x && y >= topLeft.y && z >= topLeft.z && x <= bottomRight.x && y <= bottomRight.y
               && z <= bottomRight.z;
    }

    static consteval std::array<Coord3D, 6> adjacencies() noexcept
        requires(std::is_signed_v<T>)
    {
        return {{{-1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {1, 0, 0}, {0, 0, 1}, {0, 0, -1}}};
    }

    static consteval std::array<Coord3D, 80> adjacenciesDiag() noexcept
        requires(std::is_signed_v<T>)
    {
        return {{-1, -1, -1}, {-1, -1, 0}, {-1, -1, 1}, {-1, 0, -1}, {-1, 0, 0}, {-1, 0, 1}, {-1, 1, -1},
                {-1, 1, 0},   {-1, 1, 1},  {0, -1, -1}, {0, -1, 0},  {0, -1, 1}, {0, 0, -1}, {0, 0, 1},
                {0, 1, -1},   {0, 1, 0},   {0, 1, 1},   {1, -1, -1}, {1, -1, 0}, {1, -1, 1}, {1, 0, -1},
                {1, 0, 0},    {1, 0, 1},   {1, 1, -1},  {1, 1, 0},   {1, 1, 1}};
    }

    constexpr T& operator[](const size_t idx) noexcept
    {
        switch (idx) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
            default:
                return z;
        }
    };

    constexpr T operator[](const size_t idx) const noexcept
    {
        switch (idx) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
            default:
                return z;
        }
    };

    constexpr Coord3D perm(int64_t xsel, int64_t ysel, int64_t zsel) const noexcept
        requires(std::is_signed_v<T>)
    {
        const size_t xselAbs{static_cast<size_t>(xsel < 0 ? -xsel : xsel) - 1};
        const size_t yselAbs{static_cast<size_t>(ysel < 0 ? -ysel : ysel) - 1};
        const size_t zselAbs{static_cast<size_t>(zsel < 0 ? -zsel : zsel) - 1};

        const T xSgn{xsel < 0 ? T{-1} : T{1}};
        const T ySgn{ysel < 0 ? T{-1} : T{1}};
        const T zSgn{zsel < 0 ? T{-1} : T{1}};

        return {operator[](xselAbs) * xSgn, operator[](yselAbs) * ySgn, operator[](zselAbs) * zSgn};
    }

    static consteval std::array<std::tuple<int64_t, int64_t, int64_t>, 48> perms() noexcept
        requires(std::is_signed_v<T>)
    {
        return {{{1, 2, 3},    {1, 3, 2},    {2, 1, 3},    {2, 3, 1},    {3, 1, 2},    {3, 2, 1},   {-1, 2, 3},
                 {-1, 3, 2},   {-2, 1, 3},   {-2, 3, 1},   {-3, 1, 2},   {-3, 2, 1},   {1, -2, 3},  {1, -3, 2},
                 {2, -1, 3},   {2, -3, 1},   {3, -1, 2},   {3, -2, 1},   {1, 2, -3},   {1, 3, -2},  {2, 1, -3},
                 {2, 3, -1},   {3, 1, -2},   {3, 2, -1},   {-1, -2, 3},  {-1, -3, 2},  {-2, -1, 3}, {-2, -3, 1},
                 {-3, -1, 2},  {-3, -2, 1},  {1, -2, -3},  {1, -3, -2},  {2, -1, -3},  {2, -3, -1}, {3, -1, -2},
                 {3, -2, -1},  {-1, 2, -3},  {-1, 3, -2},  {-2, 1, -3},  {-2, 3, -1},  {-3, 1, -2}, {-3, 2, -1},
                 {-1, -2, -3}, {-1, -3, -2}, {-2, -1, -3}, {-2, -3, -1}, {-3, -1, -2}, {-3, -2, -1}}};
    }

    static consteval std::array<std::tuple<int64_t, int64_t, int64_t>, 24> rots() noexcept
        requires(std::is_signed_v<T>)
    {
        return {{{1, 2, 3},  {1, -3, 2},  {1, -2, -3},  {1, 3, -2},   {3, 2, -1},   {-1, 2, -3},
                 {-3, 2, 1}, {2, -3, -1}, {-1, -3, -2}, {-2, -3, 1},  {-3, -2, -1}, {-1, -2, 3},
                 {3, -2, 1}, {-2, 3, -1}, {-1, 3, 2},   {2, 3, 1},    {-2, 1, 3},   {2, -1, 3},
                 {3, 1, 2},  {-3, -1, 2}, {2, 1, -3},   {-2, -1, -3}, {-3, 1, -2},  {3, -1, -2}}};
    }
};
