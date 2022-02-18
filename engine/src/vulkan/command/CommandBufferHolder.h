#pragma once

#include <pch.h>
#include <vulkan/command/CommandBuffer.h>

class iCommandBufferHolder
{
public:
    virtual cCommandBuffer** GetCommandBuffers() = 0;
};
