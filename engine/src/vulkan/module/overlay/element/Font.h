#pragma once

#include <pch.h>
#include <vulkan/texture/TextureInfo.h>
#include <vulkan/texture/TextureHelper.h>

class cFont
{
private:
    cLogicalDevice* ppLogicalDevice;

    VkImage poFontImage = VK_NULL_HANDLE;
    VkDeviceMemory poFontImageMemory = VK_NULL_HANDLE;

public:
    stb_fontchar* ppFontData = nullptr;

    VkImageView poFontImageView = VK_NULL_HANDLE;
    VkSampler poFontImageSampler = VK_NULL_HANDLE;

    cFont(cLogicalDevice* pLogicalDevice, uint uiFontWidth, uint uiFontHeight,
          byte* abFont24pixels, stb_fontchar* pFontData);
    ~cFont();

    uint GetFontHeight(float fFontSize);

private:
    void CreateFontImage(cLogicalDevice* pLogicalDevice, uint uiFontWidth, uint uiFontHeight, byte* abFont24pixels);
    void CreateTextureSampler(cLogicalDevice* pLogicalDevice);
};
