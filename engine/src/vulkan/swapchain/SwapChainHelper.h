#pragma once

#include <pch.h>
#include <vulkan/LogicalDevice.h>

struct tFrameBufferAttachment
{
    VkImage oImage = VK_NULL_HANDLE;
    VkDeviceMemory oMemory = VK_NULL_HANDLE;
    VkImageView oView = VK_NULL_HANDLE;
    VkFormat eFormat;
    VkAttachmentDescription tDescription;
};

class cSwapChainHelper
{
public:
    static void CreateAttachment(VkFormat eFormat,
                                 VkImageUsageFlagBits uiUsage,
                                 tFrameBufferAttachment* ptAttachment,
                                 cLogicalDevice* pLogicalDevice,
                                 VkExtent2D tSize,
                                 VkSampleCountFlagBits eSamples = VK_SAMPLE_COUNT_1_BIT);
};
