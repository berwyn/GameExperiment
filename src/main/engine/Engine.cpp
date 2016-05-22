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
	return this->renderer->Init(800, 600);
}

void Engine::Frame()
{
    static time_t last = time(NULL);

	renderer->Draw();

    time_t now = time(NULL);
    auto delta = now - last;
    last = now;
    if(delta < 16)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(16 - delta));
    }
}

void Engine::Shutdown()
{
}