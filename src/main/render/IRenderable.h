#pragma once

#include <vector>
#include "components/IComponent.h";

namespace Game::Renderer
{
    class IRenderable
    {
    public:
        inline IRenderable() {};
        inline ~IRenderable() {};

        inline auto& ComponentsForTag(const std::string& tag)
        {
            auto vec = std::vector<IComponent>();
            for (auto comp : components.begin)
            {
                if (comp.Tag() == tag)
                {
                    vec.push_back(comp);
                }
            }
            return vec;
        }

        std::vector<IComponent> components;
        std::vector<IRenderable> children;
    };
}