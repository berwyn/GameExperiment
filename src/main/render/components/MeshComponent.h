#pragma once

#include <memory>
#include "IComponent.h"
#include "main/render/IVertexBuffer.h"

namespace Game::Renderer
{
    class MeshComponent : public IComponent
    {

    public:
        inline MeshComponent() : IComponent()
        {
            this->tag = TAG;
        };

        inline ~MeshComponent() {};

        inline void Activate() {};
        inline void Deactivate() {};

        std::shared_ptr<IVertexBuffer> vertexBuffer;

    };

    const std::string MeshComponent::TAG = "MeshComponent";
}