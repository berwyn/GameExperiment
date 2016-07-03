#pragma once

#include <memory>
#include <math.h>

#include "Platform.h"

#include "../main/engine/IRenderer.h"
#include "Shaders/Triangle.h"

class GLRenderer : public IRenderer
{

public:

    inline GLRenderer(std::shared_ptr<Engine> engine): IRenderer(engine){};
    ~GLRenderer();

    bool Init(uint32_t width, uint32_t height) override;
    void Draw(int64_t, Game::Renderer::SceneGraph&) override;
    
private:
    
    GLFWwindow* window;
    TriangleShader shader;

};