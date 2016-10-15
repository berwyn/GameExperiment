#include <vector>
#include <algorithm>

#include "platform.h"
#include "DXRenderer.h"

namespace Game::DirectX
{
    auto collectAdapters() -> std::vector<IDXGIAdapter1*>
    {
        IDXGIFactory1* factory = nullptr;
        std::vector<IDXGIAdapter1*> adapters = {};
        auto hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory);

        if (FAILED(hr))
        {
            return adapters;
        }

        IDXGIAdapter1* adapter;
        for (uint32_t i = 0; factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i)
        {
            adapters.emplace_back(adapter);
        }

        factory->Release();
        return adapters;
    }

    auto scoreDevice(DXGI_ADAPTER_DESC1& desc) -> uint64_t
    {
        bool isSoftware = (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) == DXGI_ADAPTER_FLAG_SOFTWARE;
        uint64_t score = isSoftware ? 10 : 100;

        score += desc.DedicatedVideoMemory;

        return score;
    }

    auto DXRenderer::selectDevice() -> Device
    {
        std::vector<Device> devices = {};
        auto adapters = collectAdapters();

        DXGI_ADAPTER_DESC1 desc;
        for (auto& adapter : adapters)
        {
            adapter->GetDesc1(&desc);
            
            auto device = Device{ 0 };
            device.nativeDevice = &adapter;
            device.score = scoreDevice(desc);

            devices.emplace_back(device);
        }

        std::sort(devices.begin(), devices.end(), [](Device lhs, Device rhs) -> bool {
            return lhs.score > rhs.score;
        });

        return devices[0];
    }

    auto DXRenderer::selectDisplay(Device& device) -> Display
    {
        return Display{};
    }

    auto DXRenderer::createWindow(Device& device, Display& display, WindowType type) -> Window
    {
        return Window{};
    }
}
