#pragma once

#include "main/renderer/renderer.h"

namespace Game::Metal
{
    struct MTRenderer : public Renderer()
    {
    public:
        inline MTRenderer() {}
        inline ~MTRenderer() {}
        Rect getViewportBounds();
    }
}
