#include <memory>
#include <stdbool.h>
#include "engine/Engine.h"

class IGame
{
public:
	virtual ~IGame() {};

	virtual bool Init() = 0;
	virtual void Terminate() = 0;
	virtual void Loop() = 0;
};

IGame* CreateGame(std::shared_ptr<Engine>);