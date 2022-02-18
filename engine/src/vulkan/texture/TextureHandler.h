#pragma once

#include <pch.h>
#include <util/AsyncLoader.hpp>
#include <vulkan/LogicalDevice.h>
#include <vulkan/texture/Texture.h>
#include <vulkan/texture/TextureSampler.h>

// Class for loading and managing textures
class cTextureHandler : public cAsyncLoader<cTexture>
{
private:
    // Device where the textures and sampler are loaded
    cLogicalDevice* ppLogicalDevice = nullptr;

    // Texture sampler
    cTextureSampler* ppDefaultSampler = nullptr;
    cTextureSampler* ppSkyboxSampler = nullptr;

    // Map with all loaded textures
    // The key is the path to the texture
    std::map<string, cTexture*> pmpTextures;

public:
    cTextureHandler(cLogicalDevice* pLogicalDevice);
    ~cTextureHandler();

    // Load a texture from a file
    cTexture* LoadFromFile(const string& sFilePath, cTextureSampler* pSampler);
    cTexture* LoadFromFile(const string& sFilePath);

    // Returns the texture sampler
    cTextureSampler* GetDefaultSampler();
    cTextureSampler* GetSkyboxSampler();
protected:
    void LoadCallback(cTexture* pObject) override;
};;
