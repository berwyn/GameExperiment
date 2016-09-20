#pragma once

#include <stdint.h>

namespace Game::Scene2D
{
    struct Coordinate
    {
        uint32_t x, y;
    };

    struct Segment
    {
        uint32_t width, height;
    };
}