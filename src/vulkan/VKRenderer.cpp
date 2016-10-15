#include <cassert>
#include <vector>
#include <algorithm>
#include <utility>

#include "VKRenderer.h"

namespace Game::Vulkan
{
    auto createInstance() -> vk::Instance&&
    {
        auto appInfo = vk::ApplicationInfo()
            .setPNext(nullptr)
            .setPApplicationName("GameExperiment")
            .setApplicationVersion(1)
            .setPEngineName("TestEngine")
            .setEngineVersion(1)
            .setApiVersion(VK_API_VERSION_1_0);

        auto createInfo = vk::InstanceCreateInfo()
            .setPNext(nullptr)
            .setFlags(vk::InstanceCreateFlags())
            .setPApplicationInfo(&appInfo)
            .setEnabledExtensionCount(0)
            .setPpEnabledExtensionNames(nullptr)
            .setEnabledLayerCount(0)
            .setPpEnabledLayerNames(nullptr);

        vk::Instance inst;
        auto res = vk::createInstance(&createInfo, nullptr, &inst);

        if (res != vk::Result::eSuccess) {
            return nullptr;
        }

        return std::move(inst);
    }

    auto enumerateDevices(vk::Instance* instance) -> std::vector<vk::PhysicalDevice>
    {
        uint32_t count = 1;
        auto res = instance->enumeratePhysicalDevices(&count, nullptr);
        assert(count);

        auto devices = std::vector<vk::PhysicalDevice>(count);
        res = instance->enumeratePhysicalDevices(&count, devices.data());
        assert(!(int)res && count > 1);

        return devices;
    }

    auto scoreDevices(std::vector<vk::PhysicalDevice>& devices) -> void
    {
        sort(devices.begin(), devices.end(), [](vk::PhysicalDevice& lhs, vk::PhysicalDevice& rhs) -> bool {
            auto lhsProps = lhs.getProperties();
            auto rhsProps = rhs.getProperties();

            if (lhsProps.deviceType == vk::PhysicalDeviceType::eDiscreteGpu && rhsProps.deviceType != vk::PhysicalDeviceType::eDiscreteGpu)
            {
                return true;
            }
            else if (rhsProps.deviceType == vk::PhysicalDeviceType::eDiscreteGpu && lhsProps.deviceType != vk::PhysicalDeviceType::eDiscreteGpu)
            {
                return false;
            }
            else
            {
                // FIXME: For now, select the device with the newer API impl
                return lhsProps.apiVersion > rhsProps.apiVersion;
            }
        });
    }

    auto VKRenderer::selectDevice() -> Device
    {
        auto _instance = createInstance();
        auto _devices = enumerateDevices(&_instance);
        scoreDevices(_devices);
        
        instance = &_instance;
        device = &_devices[0];

        auto dev = Device{ 0 };
        dev.nativeDevice = device;

        return dev;
    }

    auto VKRenderer::selectDisplay() -> Display
    {
        return Display{};
    }

    auto VKRenderer::createWindow() -> Window
    {
        return Window{};
    }
}
