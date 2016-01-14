#include <cstdlib>
#include <iostream>

#include "Game.h"
#include "Logger.h"

#if defined(WINDOWS) && !defined(DEBUG)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
	std::shared_ptr<Engine> engine = std::make_shared<Engine>(Engine());
	IGame* game = CreateGame(engine);
	if(!game->Init())
	{
		Logger::GetInstance()->Fatal(&std::string("Failed to init, bailing!"));
	}
	game->Loop();
	game->Terminate();
	return 0;
}
