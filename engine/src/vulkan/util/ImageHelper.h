#pragma once

#include <pch.h>
#include <vulkan/vulkan.h>
#include <vulkan/PhysicalDevice.h>
#include <vulkan/LogicalDevice.h>

class cImageHelper
{
public:
    static void CreateImage(uint uiWidth,
                            uint uiHeight,
                            VkFormat eFormat,
                            VkImageTiling eTiling,
                            VkImageUsageFlags uiUsage,
                            VkMemoryPropertyFlags uiProperties,
                            VkImage& oImage,
                            VkDeviceMemory& oImageMemory,
                            cLogicalDevice* pLogicalDevice,
                            VkSampleCountFlagBits eSamples = VK_SAMPLE_COUNT_1_BIT);
    static void CreateImageView(VkImage& oImage,
                                VkFormat eFormat,
                                cLogicalDevice* pLogicalDevice,
                                VkImageView* pImageView,
                                VkImageAspectFlags uiAspectFlags);

    static VkFormat FindDepthFormat();
    static bool HasStencilComponent(VkFormat eFormat);
    static VkFormat FindSupportedFormat(const std::vector<VkFormat>& aeCandidates,
                                        VkImageTiling eTiling,
                                        VkFormatFeatureFlags uiFeatures);
};
