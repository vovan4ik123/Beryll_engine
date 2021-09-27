#pragma once

#include "SceneObject.h"
#include "Beryll/Renderer/Renderer.h"
#include "Beryll/Physics/Physics.h"

namespace Beryll
{
    // Not animated object, participates in physics simulation
    class CollidingSimpleObject : public SceneObject
    {
    public:
        CollidingSimpleObject() = delete;
        /*
         * modelPath - path to models file (.DAE or .FBX). start path from first folder inside assets/
         * canBeDisabled - true if object can be disabled from game (update/draw/playsound/simulate physics)
         *                 object can be dissabled if camera dont see it or distance is too far. For performance
         * collisionMass - mass of this object for physics simulation. 0 for static objects
         *                 for example map ground should be alwaus enabled
         * wantCollisionCallBack - if true Physics module will store actual collisions for this object,
         *                         you can check it with Physics::getIsCollision(id1, id2) or Physics::getAllCollisions()
         * collFlag - type of collision object in physics world
         * collGroup - group or groups of current object in physics world
         * collMask - should contain collGroup or groups with which you want collisions
         * vertexPath - path to vertex shader for this model
         * fragmentPath - path to fragment shader for this model
         * diffSampler - name of sampler2D .... for diffuse texture in fragment shader
         *               sampler2D .... for diffuse texture MUST be first in shader
         * specSampler - name of sampler2D .... for specular texture in fragment shader
         *               sampler2D .... for specular texture MUST be second in shader
         */
        CollidingSimpleObject(const char* modelPath,  // common params
                              bool canBeDisabled,
                              float collisionMass,    // physics params
                              bool wantCollisionCallBack,
                              CollisionFlags collFlag,
                              CollisionGroups collGroup,
                              CollisionGroups collMask,
                              const char* vertexPath, // graphics params
                              const char* fragmentPath,
                              const char* diffSampler,
                              const char* specSampler = nullptr);
        virtual ~CollidingSimpleObject();

        virtual void updateBeforePhysics() override;
        virtual void updateAfterPhysics() override;
        virtual void draw() override;
        virtual void playSound() override;

    protected:
        std::shared_ptr<VertexBuffer> m_vertexPosBuffer;
        std::shared_ptr<VertexBuffer> m_vertexNormalsBuffer;
        std::shared_ptr<VertexBuffer> m_textureCoordsBuffer;
        std::shared_ptr<IndexBuffer> m_indexBuffer;
        std::unique_ptr<VertexArray> m_vertexArray;
        std::unique_ptr<Shader> m_shader;
        std::unique_ptr<Texture> m_diffTexture;
        const uint32_t m_diffSamplerIndexInShader = 0; // diffuse sampler MUST be first in fragment shader
        std::unique_ptr<Texture> m_specTexture;
        const uint32_t m_specSamplerIndexInShader = 1; // specular sampler MUST be second in fragment shader

        glm::mat4 m_MVP{1.0f};
        glm::mat4 m_modelMatrix{1.0f};
        glm::mat4 m_scaleMatrix{1.0f};
        glm::mat4 m_rotateMatrix{1.0f};
        glm::mat4 m_translateMatrix{1.0f};
        PhysicsTransforms m_physicsTransforms;

        Assimp::Importer m_importer;
        const aiScene* m_scene = nullptr;

        static uint32_t m_allCollidingSimpleObjectCount;

    private:
        void processCollisionMesh(const aiMesh* mesh,
                                  const std::string& meshName,
                                  float mass,
                                  bool wantCallBack,
                                  CollisionFlags collFlag,
                                  CollisionGroups collGroup,
                                  CollisionGroups collMask);
    };
}