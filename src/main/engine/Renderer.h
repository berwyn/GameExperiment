#pragma once

#include <stdbool.h>
#include <stdint.h>

class Engine;

class IRenderer
{

public:

	inline IRenderer(Engine* engine) : engine(engine) {};

	virtual bool Init(uint32_t width, uint32_t height) = 0;
	virtual void Draw() = 0;

protected:

	Engine* engine;

};