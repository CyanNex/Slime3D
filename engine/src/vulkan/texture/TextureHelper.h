#pragma once

#include <pch.h>
#include <vulkan/LogicalDevice.h>
#include <vulkan/texture/TextureInfo.h>

// Helper class for textures
class cTextureHelper
{
public:
    // Copy a texture (pixels) into an image
    static void CopyTextureToImage(cLogicalDevice* pLogicalDevice,
                                   stbi_uc* pcPixels,
                                   const tTextureInfo& tTextureInfo,
                                   VkImage& oImage);

    // Change the layout of an image
    static void TransitionImageLayout(VkImage& oImage,
                                      VkFormat eFormat,
                                      VkImageLayout eOldLayout,
                                      VkImageLayout eNewLayout,
                                      cLogicalDevice* pLogicalDevice);

    // Copies data from a buffer into an image
    // Image must have a TRANSFER_DST_OPTIMAL layout
    static void CopyBufferToImage(VkBuffer& oBuffer,
                                  VkImage& oImage,
                                  uint uiWidth,
                                  uint uiHeight,
                                  cLogicalDevice* pLogicalDevice);
};
