#pragma once

#include <stdint.h>
#include <vector>

namespace Game
{
    struct Rect
    {
        uint32_t height, width, x, y;
    };

    enum WindowType
    {
        Windowed,
        Borderless,
        Fullscreen
    };

    struct Window
    {
    public:
        Rect bounds, viewport;
        WindowType type;
    };

    struct Display
    {
    public:
        uint32_t width, height;
        uint32_t density;
        uint32_t aspect;
        uint32_t refreshRate;
        bool isHDR;
    };

    struct Device
    {
    public:
        uint64_t score;
        std::vector<Display> displays;
        void* nativeDevice;
    };

    class Renderer
    {
    public:
        Renderer() {}
        virtual ~Renderer() {}

        ///
        /// \brief Iterates over the available graphics
        ///        devices and chooses the most suitable
        ///        one.
        ///
        virtual Device selectDevice() = 0;

        ///
        /// \brief Iterates over the display devices
        ///        attached to the selected device,
        ///        and selects the most appropriate one.
        ///
        /// \param[in] device The device to check adapters for
        ///
        virtual Display selectDisplay(Device& device) = 0;

        ///
        /// \brief With a given device, display, and type
        ///        creates the window.
        ///
        /// \param[in] device The device to create the window on
        /// \param[in] display The display to create the window on
        /// \param[in] type What type of window to create
        ///
        virtual Window createWindow(Device& device, Display& display, WindowType type) = 0;
    };
}
