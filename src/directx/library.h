#pragma once
#include "main/renderer/renderer.h"

extern "C"
{
    bool loadRenderer(Game::Renderer**);
    bool unloadRenderer();
}
