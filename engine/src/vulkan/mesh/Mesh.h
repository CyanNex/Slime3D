#pragma once

#include <pch.h>
#include <vulkan/util/Invalidatable.h>
#include <vulkan/geometry/Geometry.h>
#include <vulkan/texture/Texture.h>

class cMesh : public cInvalidatable
{
private:
    cGeometry* ppGeometry;
    cTexture* ppTexture;
    cTexture* ppMaterial;

public:
    cMesh(cGeometry* pGeometry, cTexture* pTexture, cTexture* pMaterial);
    cMesh(cGeometry* pGeometry, cTexture* pTexture);

    cGeometry* GetGeometry();
    cTexture* GetTexture();
    cTexture* GetMaterial();

    void SetTexture(cTexture* pTexture);
};;
