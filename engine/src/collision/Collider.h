#pragma once

#include <pch.h>
#include <collision/CollisionHelper.h>

class cCollider
{
private:
    tRectangle ptCollisionBox;
    tRectangle ptTransformedBox;

    bool pbUpdateTransformed = true;

    uint puiSize;

public:
    // Real world position of this collider
    glm::vec3 ptWorldPosition;

    cCollider(tRectangle tCollisionBox);

    // Mark that this collider should update it's transformation
    void MarkShouldUpdate();

    // Update this collider using a given transformation matrix
    void Update(glm::mat4 tOurMatrix);

    // Check if this collider collides with another collider
    // If marked as should update, will update transformation based on the given matrix
    bool Collides(glm::mat4 tOurMatrix, cCollider* pColliderB);

    // Get the size (diameter) of this collider
    uint GetSize();

    // Create a unit collider (square) optionally with a given scale
    static cCollider* UnitCollider(float fScalar = 1);
    // Create a rectangle collider with a given scale
    static cCollider* RectangleCollider(float xScale, float zScale);
    // Create a rectangle collider from two corners
    static cCollider* RectangleCollider(float x1, float z1, float x2, float z2);
};
