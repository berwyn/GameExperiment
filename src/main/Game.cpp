#include <cstdlib>
#include <iostream>
#include <thread>

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
	engine = std::make_unique<Engine>();
}

bool Game::Init()
{
	if (!engine->Init())
	{
		Logger::GetInstance()->Fatal(&std::string("Failed to initialize engine"));
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
		std::this_thread::sleep_for(16ms);
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