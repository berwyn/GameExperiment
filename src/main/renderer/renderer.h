#pragma once

namespace Game
{
    class Renderer
    {
    public:
        virtual ~Renderer() {};
        virtual Rect getViewportBounds() = 0;
    };

    struct Rect
    {
        uint32_t height, width, x, y;
    }
}