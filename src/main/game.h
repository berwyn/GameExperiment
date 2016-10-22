#pragma once

#include "sceneGraph.h"

namespace Game
{
    ///
    /// \brief
    ///     Describes the state of the engine
    ///
    enum EngineState
    {
        Preparing,  ///< Engine is preparing for use
        Prepared,   ///< Engine is ready for use
        Running,    ///< Engine is currently running
        Stopping,   ///< Engine is halting
        Stopped,    ///< Engine has halted
        Error       ///< Engine has encountered an unrecoverable error
    };

    ///
    /// \brief
    ///     An abstraction over the game loop
    ///
    class Game
    {
    public:
        Game();
        ~Game();
        
        void init();
        bool shouldClose();
        void render();
        void terminate();
        
    private:
        void* dylib;
        EngineState state;
        SceneGraph scene;
    };
}
