#pragma once
#include <vector>

namespace Game
{
    ///
    /// \brief An enum describing what phase of the render loop a component
    ///        should execute in
    ///
    enum ComponentPhase
    {
        Position,
        Movement,
        Render,
        Script,
        Physics
    };

    ///
    /// \brief A Component attaches behaviour to an entity
    ///
    class Component
    {
    public:
        ComponentPhase phase;
    };

    ///
    /// \brief An Entity describes an object that exists in the game world
    ///
    class Entity
    {
    public:

        inline Entity() : components() {}
        inline ~Entity() {}

        std::vector<Component> components;
    };

    ///
    /// \brief An EntityManger keeps track of entities, and executes their
    ///        components during the correct phase of rendering
    ///
    class EntityManager
    {
    public:
        inline void addEntity(Entity& entity)
        {
            entities.emplace_back(entity);
        }

    private:
        std::vector<Entity> entities;
    };
}
