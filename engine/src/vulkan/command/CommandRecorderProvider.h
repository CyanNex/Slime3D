#pragma once

#include <pch.h>
#include <vulkan/command/CommandBufferRecorder.h>

class iCommandRecorderProvider
{
public:
    virtual iCommandBufferRecorder* GetCommandRecorder() = 0;
};
