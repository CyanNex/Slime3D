#pragma once

#include <pch.h>
#include <scene/object/BaseObject.h>

class cLightObject : public cBaseObject
{
private:
    glm::vec3 ptColor;
    float pfRadius;

public:
    cLightObject(cMesh* pMesh, glm::vec3 tColor, float fRadius, cCollider* pCollider = nullptr, bool bStatic = true);

    glm::vec3 GetColor();
    void SetColor(const glm::vec3& oColor);

    float GetRadius();
    void SetRadius(float fRadius);
};
