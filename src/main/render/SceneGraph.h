#pragma once

#include <vector>
#include "IRenderable.h"

namespace Game::Renderer
{
    class SceneGraph
    {

    public:

        uint32_t cameraX, cameraY, cameraZ;
        std::vector<IRenderable> objects;

    };
}