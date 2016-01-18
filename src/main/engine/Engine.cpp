#include "Engine.h"

#ifdef WINDOWS

#include "../../directx/DXRenderer.h"
#define Renderer DXRenderer

#else

#include "../../opengl/GLRenderer.h"
#define Renderer GLRenderer

#endif

Engine::Engine(){}

bool Engine::Init()
{
	this->renderer = std::make_unique<Renderer>(Renderer(this));
}

void Engine::Frame()
{
}

void Engine::Shutdown()
{
}