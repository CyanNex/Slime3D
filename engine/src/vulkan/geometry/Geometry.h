#pragma once

#include <pch.h>
#include <vulkan/geometry/Vertex.h>
#include <vulkan/LogicalDevice.h>

// Class representing some geometry (vertices) that can be rendered in the scene
class cGeometry
{
protected:
    // Vertices and indices of this geometry
    std::vector<Vertex> patVertices;
    std::vector<uint> paiIndices;

    uint puiVertexCount;
    uint puiIndexCount;

    glm::vec2 ptUVScale;

    // Device where this geometry is loaded
    cLogicalDevice* ppLogicalDevice;

    string psFilePath;

    // Buffer and memory handles for the vertices and indices
    VkBuffer poVertexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory poVertexBufferMemory = VK_NULL_HANDLE;
    VkBuffer poIndexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory poIndexBufferMemory = VK_NULL_HANDLE;

public:
    cGeometry(cLogicalDevice* pLogicalDevice,
              const string& sFilePath,
              const glm::vec2& tUVScale);
    ~cGeometry();

    virtual void LoadIntoRAM();
    void CopyIntoGPU();
    void UnloadFromRAM();
    void UnloadFromGPU();

    // Returns the amount of indices in this geometry
    uint GetIndexCount();

    // Add a command to the command buffer which binds the vertex buffer
    void CmdBindVertexBuffer(VkCommandBuffer& oCommandBuffer);
    // Add a command to the command buffer which binds the index buffer
    void CmdBindIndexBuffer(VkCommandBuffer& oCommandBuffer);
};
