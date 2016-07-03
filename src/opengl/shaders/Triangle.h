#pragma once


#include <math.h>
#include <stdint.h>
#include <vector>
#include "main/render/IShader.h"


namespace Game::OpenGL::Shader
{
    class TriangleShader : Game::Renderer::IShader
    {
    public:

        uint32_t vertex;
        uint32_t fragment;
        uint32_t program;

        inline TriangleShader() {};
        ~TriangleShader();

        void Init();
        void Draw(uint32_t width, uint32_t height, time_t delta, Game::Renderer::SceneGraph& scene) override;

    private:

        uint32_t vao;
        uint32_t vbo;
        uint32_t cbo;
        uint32_t matrix;

    };
};