#pragma once
#include "main/renderer/renderer.h"

namespace Game::DirectX
{
    class DXRenderer : public Renderer
    {
    public:
        inline DXRenderer() : Renderer() {}
        inline ~DXRenderer() {}

        Device selectDevice();
        Display selectDisplay(Device& device);
        Window createWindow(Device& device, Display& display, WindowType type);
    };
}
