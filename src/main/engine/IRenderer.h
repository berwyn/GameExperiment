#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <memory>
#include "main/render/SceneGraph.h"

class Engine;

class IRenderer
{

public:

    inline IRenderer(std::shared_ptr<Engine> engine) : engine(engine) {};
    inline virtual ~IRenderer() {};

    virtual bool Init(uint32_t width, uint32_t height) = 0;
    virtual void Draw(int64_t delta, Game::Renderer::SceneGraph& scene) = 0;

protected:

    uint32_t width;
    uint32_t height;
    std::shared_ptr<Engine> engine;

};