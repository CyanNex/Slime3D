#include <scene/object/LightObject.h>

cLightObject::cLightObject(cMesh* pMesh, glm::vec3 tColor, float fRadius, cCollider* pCollider, bool bStatic)
        : cBaseObject(pMesh, pCollider, bStatic)
{
    assert(fRadius > 0);

    ptColor = tColor;
    pfRadius = fRadius;
}

glm::vec3 cLightObject::GetColor()
{
    return ptColor;
}

float cLightObject::GetRadius()
{
    return pfRadius;
}

void cLightObject::SetColor(const glm::vec3& oColor)
{
    ptColor = oColor;
}

void cLightObject::SetRadius(float fRadius)
{
    pfRadius = fRadius;
}
