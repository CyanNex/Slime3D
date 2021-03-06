#include <scene/object/BaseObject.h>

glm::mat4 cBaseObject::GetModelMatrix()
{
    // If the object is invisible, just set the scale to 0
    if (!pbVisible)
    {
        return glm::scale(glm::mat4(1.0f), glm::vec3(0));
    }

    return poModelMatrix;
}

cMesh* cBaseObject::GetMesh()
{
    return ppMesh;
}

bool cBaseObject::SetRotation(const glm::vec3 oRotation)
{
    // If the object is static and has been loaded, rotation can't be changed
    if (pbStatic && pbLoaded) return false;

    // If the object is not static, is loaded and has a collider, handle collisions
    if (!pbStatic && pbLoaded && ppCollider != nullptr)
    {
        glm::mat4 tMatrix = CalculateModelMatrix(poPosition, poScale, oRotation);
        if (HandleCollision(tMatrix)) return false;
    }

    // Update the rotation
    poRotation.x = oRotation.x;
    poRotation.y = oRotation.y;
    poRotation.z = oRotation.z;

    // If the object is static or has not been loaded, set the new matrix directly
    if (pbStatic || !pbLoaded || ppCollider == nullptr)
        poModelMatrix = CalculateModelMatrix(poPosition, poScale, poRotation);

    return true;
}

bool cBaseObject::SetPosition(const glm::vec3 oPosition)
{
    // If the object is static and has been loaded, position can't be changed
    if (pbStatic && pbLoaded) return false;

    // If the object is not static, is loaded and has a collider, handle collisions
    if (!pbStatic && pbLoaded && ppCollider != nullptr)
    {
        ppCollider->ptWorldPosition = poPosition;
        glm::mat4 tMatrix = CalculateModelMatrix(oPosition, poScale, poRotation);
        if (HandleCollision(tMatrix)) return false;
    }

    // Update the position
    poPosition.x = oPosition.x;
    poPosition.y = oPosition.y;
    poPosition.z = oPosition.z;

    // If the object is static or has not been loaded, set the new matrix directly
    if (pbStatic || !pbLoaded || ppCollider == nullptr)
        poModelMatrix = CalculateModelMatrix(poPosition, poScale, poRotation);

    return true;
}

glm::vec3 cBaseObject::GetScale()
{
    return poScale;
}

bool cBaseObject::SetScale(const glm::vec3 oScale)
{
    // If the object is static and has been loaded, scale can't be changed
    if (pbStatic && pbLoaded) return false;

    // If the object is not static, is loaded and has a collider, handle collisions
    if (!pbStatic && pbLoaded && ppCollider != nullptr)
    {
        glm::mat4 tMatrix = CalculateModelMatrix(poPosition, oScale, poRotation);
        if (HandleCollision(tMatrix)) return false;
    }

    // Update the scale
    poScale.x = oScale.x;
    poScale.y = oScale.y;
    poScale.z = oScale.z;

    // Mark the object as visible if it's not already
    pbVisible = true;

    // If the object is static or has not been loaded, set the new matrix directly
    if (pbStatic || !pbLoaded || ppCollider == nullptr)
        poModelMatrix = CalculateModelMatrix(poPosition, poScale, poRotation);

    return true;
}

glm::vec3 cBaseObject::GetPosition()
{
    return poPosition;
}

glm::vec3 cBaseObject::GetRotation()
{
    return poRotation;
}

bool cBaseObject::RotateLeft(float fAngleDiff)
{
    // If the object is static and has been loaded, rotation can't be changed
    if (pbStatic && pbLoaded) return false;

    // Calculate the new rotation vector
    glm::vec3 tNewRotation = poRotation;
    if (tNewRotation.y >= 360.0f) tNewRotation.y = 0;
    tNewRotation.y += fAngleDiff;

    return SetRotation(tNewRotation);
}

bool cBaseObject::RotateRight(float fAngleDiff)
{
    // If the object is static and has been loaded, rotation can't be changed
    if (pbStatic && pbLoaded) return false;

    // Calculate the new rotation vector
    glm::vec3 tNewRotation = poRotation;
    if (tNewRotation.y < 0.0f) tNewRotation.y = 360.0f;
    tNewRotation.y -= fAngleDiff;

    return SetRotation(tNewRotation);
}

cBaseObject::~cBaseObject()
{
    delete ppCollider;
}

bool cBaseObject::IsStatic()
{
    return pbStatic;
}

glm::mat4 cBaseObject::CalculateModelMatrix(const glm::vec3& tPosition,
                                            const glm::vec3& tScale,
                                            const glm::vec3& tRotation)
{
    glm::mat4 tMatrix(1);

    // Translation
    tMatrix = glm::translate(tMatrix, tPosition);

    // Scaling
    tMatrix = glm::scale(tMatrix, tScale);

    // Rotation
    tMatrix = CalculateRotationMatrix(tMatrix, tRotation);

    return tMatrix;
}

glm::mat4 cBaseObject::CalculateRotationMatrix(const glm::mat4& tBaseMatrix,
                                               const glm::vec3& tRotation)
{
    glm::mat4 tMatrix = tBaseMatrix;

    // Rotation around X axis
    if (tRotation.x > 0.0)
    {
        const glm::vec3 oRot_x = glm::vec3(1.0f, 0.0f, 0.0f);
        tMatrix = glm::rotate(tMatrix, glm::radians(tRotation.x), oRot_x);
    }

    // Rotation around Y axis
    if (tRotation.y > 0.0)
    {
        const glm::vec3 oRot_y = glm::vec3(0.0f, 1.0f, 0.0f);
        tMatrix = glm::rotate(tMatrix, glm::radians(tRotation.y), oRot_y);
    }

    // Rotation around Z axis
    if (tRotation.z > 0.0)
    {
        const glm::vec3 oRot_z = glm::vec3(0.0f, 0.0f, 1.0f);
        tMatrix = glm::rotate(tMatrix, glm::radians(tRotation.z), oRot_z);
    }

    return tMatrix;
}

bool cBaseObject::HandleCollision(glm::mat4 tNewMatrix)
{
    // If we collide with something, return true
    if (ppColliders->Collides(ppCollider, tNewMatrix))
    {
        return true;
    } else
    {
        // Otherwise, update the matrix and return false
        poModelMatrix = tNewMatrix;
        ppCollider->MarkShouldUpdate();
        return false;
    }
}

void cBaseObject::Setup(cColliderSet* pColliders)
{
    ppColliders = pColliders;

    if (ppCollider != nullptr)
    {
        ppCollider->ptWorldPosition = poPosition;
    }
}

cCollider* cBaseObject::GetCollider()
{
    return ppCollider;
}

bool cBaseObject::SetPosition(float x, float z)
{
    // If the object is static and has been loaded, position can't be changed
    if (pbStatic && pbLoaded) return false;

    // If the object is not static, is loaded and has a collider, handle collisions
    if (!pbStatic && pbLoaded && ppCollider != nullptr)
    {
        ppCollider->ptWorldPosition = poPosition;
        glm::vec3 oPosition = {x, poPosition.y, z};
        glm::mat4 tMatrix = CalculateModelMatrix(oPosition, poScale, poRotation);
        if (HandleCollision(tMatrix)) return false;
    }

    // Update the position
    poPosition.x = x;
    poPosition.z = z;

    // If the object is static or has not been loaded, set the new matrix directly
    if (pbStatic || !pbLoaded || ppCollider == nullptr)
        poModelMatrix = CalculateModelMatrix(poPosition, poScale, poRotation);

    return true;
}

cBaseObject::cBaseObject(cMesh* pMesh, cCollider* pCollider, bool bStatic)
{
    ppMesh = pMesh;
    ppCollider = pCollider;
    pbStatic = bStatic;
}

