#pragma once

#include <pch.h>
#include <vulkan/texture/TextureInfo.h>
#include <vulkan/texture/TextureSampler.h>

// Class representing a texture
class cTexture
{
private:
    // Logical device where this texture is loaded
    cLogicalDevice* ppLogicalDevice;

    // Path to the texture file on disk
    string psFilePath;

    // Information about this texture
    tTextureInfo ptTextureInfo;

    // Pointer to the pixel data in RAM
    stbi_uc* ppcPixels = nullptr;

    // Texture image, memory and image view handles
    VkImage poTextureImage = VK_NULL_HANDLE;
    VkDeviceMemory poTextureImageMemory = VK_NULL_HANDLE;
    VkImageView poTextureImageView = VK_NULL_HANDLE;

    // Sampler to use for this texture
    cTextureSampler* ppSampler;

public:
    cTexture(cLogicalDevice* pLogicalDevice,
             const string& sFilePath,
             cTextureSampler* pSampler);
    ~cTexture();

    // Methods for loading and unloading the texture
    void LoadIntoRAM();
    void CopyIntoGPU();
    void UnloadFromRAM();
    void UnloadFromGPU();

    // Returns the information about this texture
    tTextureInfo GetTextureInfo();
    // Returns the image view for this texture
    VkImageView& GetView();
    // Returns the sampler to use for this texture
    VkSampler& GetSampler();
};
