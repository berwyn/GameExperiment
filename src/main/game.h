#pragma once

#include "sceneGraph.h"

namespace Game
{
    enum EngineState
    {
        Preparing,
        Prepared,
        Running,
        Stopping,
        Stopped,
        Error
    };
    
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
