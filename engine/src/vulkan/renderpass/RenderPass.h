#pragma once

#include <pch.h>
#include <vulkan/LogicalDevice.h>

class cRenderPass
{
protected:
    VkRenderPass poRenderPass = VK_NULL_HANDLE;

    cLogicalDevice* ppLogicalDevice;

public:
    cRenderPass(cLogicalDevice* pLogicalDevice);
    ~cRenderPass();

    VkRenderPass& GetRenderPass();
};
