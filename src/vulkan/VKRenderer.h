#pragma once

#include <memory>
#include <math.h>

#include "../main/engine/Renderer.h"

class VKRenderer : public IRenderer
{
public:

	inline VKRenderer(std::shared_ptr<Engine> engine) : IRenderer(engine){};
	~VKRenderer();

	bool Init(uint32_t width, uint32_t height) override;
	void Draw() override;
};