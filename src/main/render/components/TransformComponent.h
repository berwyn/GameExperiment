#pragma once

#include "main/render/components/IComponent.h"

namespace Game::Renderer
{
    class TransformComponent : public IComponent
    {
        inline TransformComponent() : IComponent()
        {
            tag = TAG;
        }

        inline ~TransformComponent() {}

        inline void Activate() override
        {

        }

        inline void Deactivate() override
        {

        }

        int32_t x, y, z;
    };

    const std::string TransformComponent::TAG = "TransformComponent";
}