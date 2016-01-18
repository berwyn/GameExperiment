#include <memory>
#include <stdbool.h>
#include "engine/Engine.h"

class Game
{

public:

	Game();

	bool Init();
	void Loop();
	void Terminate();

private:

	std::unique_ptr<Engine> engine;

};