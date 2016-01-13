#pragma once

#include <memory>
#include <stdint.h>
#include "Canvas.h"

class Engine
{
public:
    std::shared_ptr<Canvas> renderCanvas;
    std::shared_ptr<Canvas> uiCanvas;
    
	bool inForeground;
	uint32_t frameLock;
	uint32_t backgroundFrameLock;

    Engine();
    void Frame();
};
