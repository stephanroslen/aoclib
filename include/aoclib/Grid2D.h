#pragma once

#include "Coord2D.h"

#include <vector>

namespace detail {

template <std::signed_integral CT, typename T>
struct Grid2D {
    using Coord = Coord2D<CT>;

    Coord gridSize{0, 0};

    std::vector<T> data{};

    Grid2D() = default;

    Grid2D(const Coord& gridSize_, auto&& initializer)
        : gridSize{gridSize_}
        , data(gridSize.x * gridSize.y, T{})
    {
        eachCoord([&](const Coord& coord) { at(coord) = initializer(coord); });
    }

    bool isOnGrid(const Coord& coord) const noexcept
    {
        return coord.isInRectangle({0, 0}, gridSize - Coord{1, 1});
    }

    void eachCoord(auto&& morphism) const noexcept
    {
        for (CT iy{0}; iy < gridSize.y; ++iy) {
            for (CT ix{0}; ix < gridSize.x; ++ix) {
                const Coord coord{ix, iy};
                morphism(coord);
            }
        }
    }

    void eachValue(auto&& morphism) const noexcept
    {
        eachCoord([&](const Coord& coord) { morphism(at(coord)); });
    }

    void eachValue(auto&& morphism) noexcept
    {
        eachCoord([&](const Coord& coord) { morphism(at(coord)); });
    }

    size_t coordToIdx(const Coord& coord) const noexcept
    {
        return coord.x + coord.y * gridSize.x;
    }

    decltype(auto) at(const Coord& coord) noexcept
    {
        return data.at(coordToIdx(coord));
    }

    decltype(auto) at(const Coord& coord) const noexcept
    {
        return data.at(coordToIdx(coord));
    }
};

template <typename CT, typename T>
struct Grid2DSelect {
    using Type = Grid2D<CT, T>;
};

template <typename CT, typename T>
struct Grid2DSelect<Coord2D<CT>, T> {
    using Type = Grid2D<CT, T>;
};

}

template <typename CT, typename T>
using Grid2D = typename detail::Grid2DSelect<CT, T>::Type;
