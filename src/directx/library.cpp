#include "library.h"
#include "DXRenderer.h"

using namespace Game::DirectX;

auto loadRenderer(Game::Renderer** renderer) -> bool
{
    auto rndr = DXRenderer();
    *renderer = &rndr;
    return true;
}

auto unloadRenderer() -> bool
{
    return true;
}
