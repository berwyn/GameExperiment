#pragma once

#include <memory>
#include <stdint.h>

#include "Renderer.h"

class Engine
{

public:

	Engine();

	bool ShouldHalt;
	bool IsInErrorState;

	bool Init();
	void Frame();
	void Shutdown();

private:

	std::unique_ptr<IRenderer> renderer;

};