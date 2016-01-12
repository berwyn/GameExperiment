#include <stdbool.h>

class IGame
{
public:
	virtual ~IGame() {};

	virtual bool Init() 		= 0;
	virtual void Terminate() 	= 0;
	virtual void Loop() 		= 0;
};

IGame* CreateGame();