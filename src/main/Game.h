#include <memory>
#include <stdbool.h>

#include "engine/Engine.h"
#include "engine/Renderer.h"

class Game
{

public:

	Game();

	bool Init();
	void Loop();
	void Terminate();

private:

	std::shared_ptr<Engine> engine;
	std::shared_ptr<IRenderer> renderer;

};