#pragma once

#include <vector>
#include <stdbool.h>

namespace Game::Renderer
{

    class IVertexBuffer
    {
    public:
        inline IVertexBuffer() {};
        inline virtual ~IVertexBuffer() {};

        virtual bool LoadStaticMesh(std::vector<float_t> vertices) = 0;
        virtual bool LoadStaticColors(std::vector<float_t> colors) = 0;
    };
}

