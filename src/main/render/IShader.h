#pragma once

#include <stdint.h>
#include <time.h>
#include "SceneGraph.h"

namespace Game::Renderer
{
    class IShader
    {
    public:
        inline IShader() {};
        inline ~IShader() {};

        virtual void Draw(uint32_t width, uint32_t height, time_t delta, SceneGraph& scene) = 0;
    };
}