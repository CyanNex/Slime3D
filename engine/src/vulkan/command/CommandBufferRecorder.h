#pragma once

#include <pch.h>
#include <vulkan/vulkan.h>

class iCommandBufferRecorder
{
public:
    virtual ~iCommandBufferRecorder() = default;

    virtual void Setup(uint uiIndex) = 0;
    virtual void RecordCommands(VkCommandBuffer& oCommandBuffer, uint uiIndex) = 0;
};
