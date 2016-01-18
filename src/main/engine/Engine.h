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

	bool Init(std::shared_ptr<IRenderer> renderer);
	void Frame();
	void Shutdown();

private:

	std::shared_ptr<IRenderer> renderer;

};