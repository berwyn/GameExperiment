#include <cstdlib>
#include <iostream>

#include "Game.h"
#include "Logger.h"

#if defined(WINDOWS) && !defined(DEBUG)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main(int argc, int* argv[])
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
	engine = std::make_unique<Engine>(Engine());
}

bool Game::Init()
{
	if (!engine->Init())
	{
		Logger::GetInstance()->Fatal(&std::string("Failed to initialize engine"));
		engine->ShouldHalt = true;
		return false;
	}
	return true;
}

void Game::Loop()
{
	while (!engine->ShouldHalt)
	{
		// Do stuff with actors here
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