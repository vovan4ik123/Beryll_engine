#pragma once

#include "LibsHeaders.h"
#include "CppHeaders.h"

namespace Beryll
{
    // base class of all game objects in game (3d scene and GUI objects)
    // game objects are handled in layers in game state
    class GameObject
    {
    public:
        virtual ~GameObject() {}

        virtual void updateBeforePhysics() = 0; // handle users input, move objects, Physics::setTransforms() here
        virtual void updateAfterPhysics() = 0; // update positions after symulation, resolve collisions, Physics::getTransforms() here
        virtual void draw() = 0; // subclass graphics
        virtual void playSound() = 0; // subclass sounds

        const std::string& getID() { return m_ID; }
        const glm::vec3& getPosition() { return m_position; }
        void setPosition(const glm::vec3& pos) { m_position = pos; }

        bool getHasCollisionObject() { return m_hasCollisionObject; }
        bool getCanBeDisabled() { return m_canBeDisabled; }

        // use it for dissable object from update/draw/sound loops
        bool getIsEnabled() { return m_isEnabled; }
        void enable() { m_isEnabled = true; }
        void disable() { if(m_canBeDisabled) { m_isEnabled = false; } }

    protected:
        std::string m_ID; // initialize in subbclass
        glm::vec3 m_position{0.0f};
        // set true for all collision objects
        bool m_hasCollisionObject = false;
        // some objects can not be disabled from update/draw/playSound/simulation. Ground for example
        // make map grounds m_canBeDisabled = false; in its constructor
        bool m_canBeDisabled = true;

    private:
        // disable object for performance
        bool m_isEnabled = true;
    };
}
