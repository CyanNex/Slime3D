#pragma once

#include <pch.h>
#include <vulkan/vulkan.h>
#include <vulkan/LogicalDevice.h>
#include <mutex>

// Helper class for using vulkan commands
class cCommandHelper
{
public:
    // TODO: This should be moved from a static field to a separate class
    static VkCommandPool poCommandPool;
    static std::mutex ptCommandPoolMutex;

    // Setup a command pool on a logical device
    static void SetupCommandPool(cLogicalDevice* pLogicalDevice);

    // Start a one time command and return the command buffer
    static VkCommandBuffer BeginSingleTimeCommands(cLogicalDevice* pLogicalDevice);
    // End and submit a one time command and clean up the command buffer
    static void EndSingleTimeCommands(cLogicalDevice* pLogicalDevice, VkCommandBuffer oCommandBuffer);
};
