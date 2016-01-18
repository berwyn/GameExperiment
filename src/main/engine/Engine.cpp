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
	renderer->Draw();
}

void Engine::Shutdown()
{
}