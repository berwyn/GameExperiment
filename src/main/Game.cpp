#include <cstdlib>
#include <iostream>
#include <thread>

#include "Game.h"
#include "Logger.h"

#if defined(WINDOWS) && !defined(DEBUG)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#ifdef WINDOWS

#include "../directx/DXRenderer.h"
#define Renderer DXRenderer

#else

#include "../opengl/GLRenderer.h"
#define Renderer GLRenderer

#endif

int main(int argc, char* argv[])
{
	auto game = Game();
	if(game.Init())
	{
		game.Loop();
	}
	game.Terminate();
	return 0;
}

Game::Game()
{
	engine = std::make_shared<Engine>();
	renderer = std::make_shared<Renderer>(engine);
}

bool Game::Init()
{
	if (!engine->Init(renderer))
	{
        auto message = std::make_unique<std::string>("Failed to initialize engine");
		Logger::GetInstance()->Fatal(message.get());
		return false;
	}
	return true;
}

void Game::Loop()
{
	while (!engine->ShouldHalt)
	{
		using namespace std::literals;
		// TODO: Do real things here
		engine->Frame();
	}
}

void Game::Terminate()
{

#ifdef DEBUG
	if (engine->IsInErrorState)
	{
		// TODO: Shutdown GUI but wait for input before closing console
	}
#endif

	engine->Shutdown();
}