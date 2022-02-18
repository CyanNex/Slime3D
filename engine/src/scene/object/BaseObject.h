#pragma once

#include <pch.h>
#include <vulkan/mesh/Mesh.h>
#include <collision/ColliderSet.h>

class cBaseObject
{
protected:
    cMesh* ppMesh;
    bool pbStatic;

    cColliderSet* ppColliders;

    glm::vec3 poRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 poPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 poScale = glm::vec3(1.0f, 1.0f, 1.0f);

    glm::mat4 poModelMatrix = glm::mat4(1);

public:
    // When set to false, this object will be invisible
    bool pbVisible = true;

    // When set to false, this object will skip the lighting pass and will only be lit by ambient light
    bool pbLighting = true;

    // Index to the uniform buffer for this object
    uint puiUniformIndex;

    // True once this object is fully loaded into the world
    bool pbLoaded = false;

    // The collider for this object
    cCollider* ppCollider;


    cBaseObject(cMesh* pMesh, cCollider* pCollider = nullptr, bool bStatic = true);
    virtual ~cBaseObject();

    void Setup(cColliderSet* pColliders);

    glm::mat4 GetModelMatrix();
    cMesh* GetMesh();
    bool IsStatic();
    cCollider* GetCollider();

    bool SetRotation(glm::vec3 poRotation);
    bool SetPosition(glm::vec3 poPosition);
    bool SetPosition(float x, float z);
    bool SetScale(glm::vec3 poScale);
    glm::vec3 GetScale();
    glm::vec3 GetPosition();
    glm::vec3 GetRotation();
    bool RotateLeft(float fAngleDiff);
    bool RotateRight(float fAngleDiff);

private:
    bool HandleCollision(glm::mat4 tNewMatrix);

    static glm::mat4 CalculateModelMatrix(const glm::vec3& tPosition,
                                          const glm::vec3& tScale,
                                          const glm::vec3& tRotation);
    static glm::mat4 CalculateRotationMatrix(const glm::mat4& tBaseMatrix,
                                             const glm::vec3& tRotation);
};

typedef cBaseObject cModel;
