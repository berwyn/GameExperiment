#include <cstdlib>
#include <iostream>
#include "Game.hpp"

int main()
{
	IGame* game = CreateGame();
	if(!game->Init())
	{
		std::cerr << "Failed to init, bailing!" << std::endl;
	}
	game->Loop();
	game->Terminate();
	return 0;
}
