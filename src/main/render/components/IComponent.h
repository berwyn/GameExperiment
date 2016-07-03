#pragma once

#include <string>
#include <stdint.h>
#include <stdbool.h>

namespace Game::Renderer
{
    class IComponent
    {
    public:
        inline IComponent() {};
        virtual ~IComponent() {};
        virtual void Activate() = 0;
        virtual void Deactivate() = 0;

        static const std::string TAG;

        inline const std::string& Tag()
        {
            return tag;
        }

    protected:
        std::string tag;
    };
};