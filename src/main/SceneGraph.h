#pragma once

#include <unordered_map>

#include "componentManager.h"
#include "scene2d/scene2d.h"
#include "scene3d/scene3d.h"

namespace Game
{
    class SceneGraph
    {
    public:
        inline SceneGraph() {} : em();
        inline ~SceneGraph() {}

    private:
        EntityManager em;
    };

    ///
    /// \brief Scene component for 2D games
    ///
    class Scene2D : public SceneGraph
    {
    public:
        ///
        /// \brief Creates a new Scene2D with a fixed number of segments in
        ///        width and height.
        ///
        /// \param width    The number of segments to use for the width of the
        ///                 SceneGraph.
        /// \param height   The number of segments to use for the height of the
        ///                 SceneGraph.
        ///
        /// This variant of the Scene2D constructor will create a grid with a
        /// fixed number of segments in width, and a fixed number of segments
        /// in height. At runtime, this may cause stretching of the segments
        /// in order to accomodate them inside the viewport.
        /// __TODO:__ Document how to disable resizing or lock aspect ratio.
        ///
        inline Scene2D(uint32_t width, uint32_t height) : SceneGraph()
        {
            this->width = width;
            this->height = height;
            screenspace = std::unordered_map<Scene2D::Coordinate, Scene2D::Segment>(width * height);

            for(auto x = 0; x < width; x++)
            {
                for(auto y = 0; y < width; y++)
                {
                    auto coord = Scene2DCoordinate{ x, y };
                    screenspace[coord] = Scene2D::Segment{};
                }
            }
        }

        ///
        /// \brief Creates a new Scene2D with segments of a fixed size, creating
        ///        as many as needed to fill the viewport.
        ///
        /// \param reference    A Scene2DSegment to use as a template for the
        ///                     rest of the segments in the SceneGraph;
        ///
        /// This variant of the Scene2D constructor will create a grid where the
        /// segments are of a fixed size, but the number used to cover the
        /// viewport can fluctuate to fill the player's view.'
        ///
        inline Scene2D(Scene2D::Segment& reference): SceneGraph()
        {
            
        }

        inline ~Scene2D() {}

    private:
        uint32_t width, height;
        std::unordered_map<Scene2DC::oordinate, Scene2D::Segment> screenspace;
    };

    ///
    /// \brief A scene for 3D games
    ///
    class Scene3D : public SceneGraph
    {
    public:
        ///
        /// \brief Creates a new Scene3D
        ///
        inline Scene3D() : SceneGraph()
        {

        }
        inline ~Scene3D() {}
    };
}