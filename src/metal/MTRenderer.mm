#include "MTRenderer.h"

namespace Game::Metal
{
    auto MTRenderer::getViewportBounds() -> Rect
    {
        return Rect { 0, 0, 0, 0 };
    }
}
