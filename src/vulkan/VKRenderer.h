#pragma once

#include <vulkan/vulkan.hpp>
#include "main/renderer/renderer.h"

namespace Game::Vulkan
{
    struct VKRenderer : public Renderer
    {
    public:
        inline VKRenderer() {}
        inline ~VKRenderer() {}

        Device selectDevice();
        Display selectDisplay();
        Window createWindow();

    private:
        vk::Instance* instance;
        vk::PhysicalDevice* device;
    };
}
