#include "Engine.h"

#ifdef WINDOWS

#include "../../directx/DXRenderer.h"
#define Renderer DXRenderer

#else

#include "../../opengl/GLRenderer.h"
#define Renderer GLRenderer

#endif

Engine::Engine()
{
	ShouldHalt = false;
	IsInErrorState = false;
	renderer = std::make_unique<Renderer>(this);
}

bool Engine::Init()
{
	return renderer->Init(800, 600);
}

void Engine::Frame()
{
	renderer->Draw();
}

void Engine::Shutdown()
{
}