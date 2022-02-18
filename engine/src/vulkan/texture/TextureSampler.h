#pragma once

#include <pch.h>
#include <vulkan/vulkan.h>
#include <vulkan/LogicalDevice.h>

class cTextureSampler
{
private:
    cLogicalDevice* ppLogicalDevice;

    VkSampler poTextureSampler = VK_NULL_HANDLE;

public:
    cTextureSampler(cLogicalDevice* pLogicalDevice,
                    VkFilter eFilter,
                    VkSamplerAddressMode eAddressMode,
                    bool bAnisotropy);
    ~cTextureSampler();

    VkSampler& GetSampler();
};
