#pragma once

#include <pch.h>
#include <vulkan/LogicalDevice.h>
#include <vulkan/geometry/Geometry.h>

class cViewportQuadGeometry : public cGeometry
{
public:
    static cViewportQuadGeometry* GEOMETRY;

    static void Init(cLogicalDevice* pLogicalDevice);
    static void Destroy(cLogicalDevice* pLogicalDevice);
    void LoadIntoRAM() override;

private:
    cViewportQuadGeometry(cLogicalDevice* pLogicalDevice);

    static Vertex CreateVertex(glm::vec3 tPosition, glm::vec2 tTextureCoord);
};
