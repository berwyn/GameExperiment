#pragma once
#include <stdint.h>

namespace Game::Scene2D
{
    struct Coordinate
    {
        uint32_t x, y;

        bool operator ==(const Coordinate& other) const {
            return x == other.x && y == other.y;
        }
    };

    struct Segment
    {
        uint32_t width, height;
    };
}

namespace std
{
    template<> struct hash<Game::Scene2D::Coordinate>
    {
        size_t operator()(Game::Scene2D::Coordinate const& c) const
        {
            size_t const x(hash<uint32_t>{}(c.x));
            size_t const y(hash<uint32_t>{}(c.y));
            return x ^ (y << 1);
        }
    };
}
