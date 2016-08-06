#pragma once

#include <unordered_map>
#include "scene2d/scene2d.h"

namespace Game
{
    class SceneGraph
    {
    public:
        inline SceneGraph() {}
        inline ~SceneGraph() {}
    };

    ///
    /// \brief Scene component for 2D games
    ///
    ///
    ///
    class Scene2D : public SceneGraph
    {
    public:
        inline Scene2D(uint32_t width, uint32_t height) : SceneGraph()
        {

        }

        inline ~Scene2D() {}

        std::unordered_map<Scene2DCoordinate, Scene2DSegment> screenspace;
    };

    class Scene3D : public SceneGraph
    {
    public:
        inline Scene3D() : SceneGraph() {}
        inline ~Scene3D() {}
    };
}