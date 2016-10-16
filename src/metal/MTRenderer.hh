#pragma once

#include "platform.hh"
#include "main/renderer/renderer.h"

namespace Game::Metal
{
    struct MTRenderer : public Renderer
    {
    public:
        inline MTRenderer() {}
        inline ~MTRenderer() {}

        bool setup();
        bool createWindow(uint32_t width, uint32_t height, WindowType type);
    
    private:
        id<MTLDevice> device;
        NSWindow* window;
        MTKView* view;
    };
}
