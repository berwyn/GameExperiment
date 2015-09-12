#include <cstdlib>
#include <iostream>
#include "Game.hpp"

int main()
{	
	Game* game = new Game();
	if(!game->Init())
	{
		std::cerr << "Failed to init, bailing!" << std::endl;
	}
	game->Loop();
	game->Terminate();
	return 0;
}