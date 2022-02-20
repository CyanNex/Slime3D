#pragma once

#include <pch.h>
#include <vulkan/LogicalDevice.h>
#include <vulkan/geometry/Geometry.h>

class cViewportQuadGeometry : public cGeometry
{
public:
    static cViewportQuadGeometry* FULL_FRAME;
    static cViewportQuadGeometry* HALF_FRAME;

    static void Init(cLogicalDevice* pLogicalDevice);
    static void Destroy(cLogicalDevice* pLogicalDevice);
    void LoadIntoRAM() override;

private:
    cViewportQuadGeometry(cLogicalDevice* pLogicalDevice, float fScale = 1.0f);

    static Vertex CreateVertex(glm::vec3 tPosition, glm::vec2 tTextureCoord);
};
