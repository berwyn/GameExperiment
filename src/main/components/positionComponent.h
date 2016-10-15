#pragma once
#include "../componentManager.h"

namespace Game::Components
{
    class PositionComponent : public Component
    {
    public:
        uint32_t x, y, z;

        inline PositionComponent() : Component()
        {
            phase = ComponentPhase::Position;
            x = y = z = 0;
        }
        
        inline ~PositionComponent() {}
    };
}
