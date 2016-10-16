#include <cstdlib>

#include "game.h"
#include "platform.h"

#ifdef APPLE
    #define DYLIB "libMetal.dylib"
#elif defined(LINUX)
    #define DYLIB "libmetal.so"
#else
    #define DYLIB "libmetal.dll"
#endif

int main(int argc, char* argv[])
{
    auto game = Game::Game();
    game.init();
    while (!game.shouldClose())
    {
        game.render();
    }
    game.terminate();
    return EXIT_SUCCESS;
}

namespace Game
{
    Game::Game()
    {
        auto str = std::string(DYLIB);
        auto res = Platform::loadDylib(str, dylib);
        if(res == false)
        {
            // TODO: Handle bind fail
        }
        state = EngineState::Preparing;
        // TODO: Setup state
    }
    
    Game::~Game()
    {
        // TODO: Local cleanup
        state = EngineState::Stopped;
    }
    
    auto Game::init() -> void
    {
        // TODO: Renderer initialisation
        state = EngineState::Prepared;
    }
    
    auto Game::shouldClose() -> bool
    {
        // TODO: Actually determine if game should close
        return false;
    }
    
    auto Game::render() -> void
    {
        if (state == EngineState::Prepared)
        {
            state = EngineState::Running;
            // TODO: Handle first-run situation
        }
    }
    
    auto Game::terminate() -> void
    {
        state = EngineState::Stopping;
        // TODO Halt the renderer
    }
}
