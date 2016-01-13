#include "Engine.h"

Engine::Engine()
{
	Canvas _uiCanvas = Canvas{ 800.0f, 600.0f, 1.0f };
	Canvas _renderCanvas = Canvas{ 800.0f, 600.0f, 1.0f };

	uiCanvas = std::make_shared<Canvas>(_uiCanvas);
	renderCanvas = std::make_shared<Canvas>(_renderCanvas);
}

void Engine::Frame()
{
}
