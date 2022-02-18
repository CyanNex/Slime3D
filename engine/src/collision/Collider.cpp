#include <collision/Collider.h>

cCollider::cCollider(tRectangle tCollisionBox)
{
    ptCollisionBox = tCollisionBox;

    puiSize = (uint) glm::distance(tCollisionBox.aVertices[0], tCollisionBox.aVertices[2]);
    if (puiSize == 0) puiSize = 1;
}

void cCollider::MarkShouldUpdate()
{
    pbUpdateTransformed = true;
}

void cCollider::Update(glm::mat4 tOurMatrix)
{
    ptTransformedBox = cCollisionHelper::TransformRectangle(ptCollisionBox, tOurMatrix);
}

bool cCollider::Collides(glm::mat4 tOurMatrix, cCollider* pColliderB)
{
    if (pbUpdateTransformed)
    {
        Update(tOurMatrix);
    }

    return cCollisionHelper::Collides(ptTransformedBox, pColliderB->ptTransformedBox);
}

uint cCollider::GetSize()
{
    return puiSize;
}

cCollider* cCollider::UnitCollider(float fScalar)
{
    return RectangleCollider(fScalar, fScalar);
}

cCollider* cCollider::RectangleCollider(float xScale, float zScale)
{
    tRectangle tRectangle = {};
    tRectangle.aVertices[0] = glm::vec2(0, 0);
    tRectangle.aVertices[1] = glm::vec2(0, -zScale);
    tRectangle.aVertices[2] = glm::vec2(xScale, -zScale);
    tRectangle.aVertices[3] = glm::vec2(xScale, 0);
    return new cCollider(tRectangle);
}

cCollider* cCollider::RectangleCollider(float x1, float z1, float x2, float z2)
{
    tRectangle tRectangle = {};
    tRectangle.aVertices[0] = glm::vec2(x1, z1);
    tRectangle.aVertices[1] = glm::vec2(x1, z2);
    tRectangle.aVertices[2] = glm::vec2(x2, z2);
    tRectangle.aVertices[3] = glm::vec2(x2, z1);
    return new cCollider(tRectangle);
}
