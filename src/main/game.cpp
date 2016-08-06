#include <cstdlib>

namespace game
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
        Game()
        {
            state = EngineState::Preparing;
            // TODO: Setup state
        }

        ~Game()
        {
            // TODO: Local cleanup
            state = EngineState::Stopped;
        }

        void init()
        {
            // TODO: Renderer initialisation
            state = EngineState::Prepared;
        }

        bool shouldClose()
        {
            // TODO: Actually determin if game should close
            return false;
        }

        void render()
        {
            if (state == EngineState::Prepared)
            {
                state = EngineState::Running;
                // TODO: Handle first-run situation
            }
        }

        void terminate()
        {
            state = EngineState::Stopping;
            // TODO Halt the renderer
        }

    private:
        EngineState state;
    };
}

int main(int argc, char* argv[])
{
    auto game = game::Game();
    game.init();
    while (!game.shouldClose())
    {
        game.render();
    }
    game.terminate();
    return EXIT_SUCCESS;
}