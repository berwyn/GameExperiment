#pragma once

#include <memory>

#include "Platform.h"

#include "../main/engine/Renderer.h"
#include "Shaders/Triangle.h"

class GLRenderer : public IRenderer
{

public:

    inline GLRenderer(std::shared_ptr<Engine> engine): IRenderer(engine), shader(nullptr){};
    bool Init(uint32_t width, uint32_t height) override;
    void Draw() override;
    
private:
    
    GLFWwindow* window;
    TriangleShader shader;

};