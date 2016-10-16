#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <vector>

namespace Game
{
    ///
    /// \brief
    ///     An enum of supported window types
    ///
    enum WindowType
    {
        Windowed,   ///< A standard titled window
        Borderless, ///< A window which fills the display with no chrome
        Fullscreen  ///< Exclusive fullscreen
    };

    ///
    /// \brief
    ///     An abstraction over rendering tasks
    ///
    class Renderer
    {
    public:
        Renderer() {}
        virtual ~Renderer() {}

        ///
        /// \brief
        ///     Initialise the the renderer and allocate all basic objects
        /// \return
        ///     a boolean indicating whether the operation was successful
        ///
        virtual bool setup() = 0;
        
        ///
        /// \brief
        ///     Create the window and display it to the user
        ///
        /// \param[in] width The width of the window at 96dpi
        /// \param[in] height The height of the window at 96dpi
        /// \param[in] type What window type to create
        ///
        /// \return
        ///     a boolean indicating whether the operation was successful
        ///
        virtual bool createWindow(uint32_t width, uint32_t height, WindowType type) = 0;
    };
}
