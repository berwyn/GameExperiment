#include <chrono>
#include <thread>
#include <time.h>

#include "Engine.h"

Engine::Engine()
{
    ShouldHalt = false;
    IsInErrorState = false;
}

bool Engine::Init(std::shared_ptr<IRenderer> renderer)
{
    this->renderer = renderer;
    sceneGraph = Game::Renderer::SceneGraph();
    frameTime = time(NULL);
    return this->renderer->Init(800, 600);
}

void Engine::Frame()
{
    int64_t frameDelta = time(NULL) - frameTime;

    renderer->Draw(frameDelta, sceneGraph);

    time_t now = time(NULL);
    int64_t delta = now - frameTime;
    frameTime = now;
    if(delta < 16)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(16 - delta));
    }
}

void Engine::Shutdown()
{
}