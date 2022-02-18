#pragma once

#include <pch.h>
#include <vulkan/vulkan.h>
#include <vulkan/LogicalDevice.h>
#include <vulkan/PhysicalDevice.h>
#include <vulkan/command/CommandHelper.h>

// Helper class for dealing with Vulkan buffers and device memory
class cBufferHelper
{
public:
    // Sets up a new buffer on the device and copies the data to it
    static void CopyToNewBuffer(cLogicalDevice* pLogicalDevice,
                                VkMemoryPropertyFlags uiProperties,
                                void* pData, VkDeviceSize ulSize,
                                VkBuffer& oBuffer, VkDeviceMemory& oBufferMemory);

    // Creates a buffer based on specified parameters
    static void CreateBuffer(cLogicalDevice* pLogicalDevice,
                             VkDeviceSize ulSize,
                             VkBufferUsageFlags uiUsage,
                             VkMemoryPropertyFlags uiProperties,
                             VkBuffer& oBuffer,
                             VkDeviceMemory& oBufferMemory);

    // Copies the data in a buffer to another buffer
    static void CopyBuffer(VkBuffer& oSrcBuffer,
                           VkBuffer& oDstBuffer,
                           VkDeviceSize ulSize,
                           cLogicalDevice* pLogicalDevice);

    // Find a memory type which is matching the filter and flags and is
    // supported by the selected physical device
    static uint FindMemoryType(uint uiTypeFilter, VkMemoryPropertyFlags tProperties);
};
