#pragma once

#include <stdint.h>
#include "main/render/IVertexBuffer.h"

namespace Game::OpenGL
{
    class GLVertexBuffer : public Game::Renderer::IVertexBuffer
    {

    public:

        GLVertexBuffer();
        ~GLVertexBuffer();

        bool LoadStaticMesh(std::vector<float_t> vertices) override;
        bool LoadStaticColors(std::vector<float_t> colors) override;

        uint32_t vbo;
        uint32_t cbo;
        uint32_t vao;

    };
}