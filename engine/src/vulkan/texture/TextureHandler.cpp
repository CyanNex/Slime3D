#include <vulkan/texture/TextureHandler.h>

cTextureHandler::cTextureHandler(cLogicalDevice* pLogicalDevice) : cAsyncLoader<cTexture>(4)
{
    assert(pLogicalDevice != nullptr); // logical device must exist

    // Store the logical device
    ppLogicalDevice = pLogicalDevice;

    ppDefaultSampler = new cTextureSampler(pLogicalDevice,
                                           VK_FILTER_LINEAR,
                                           VK_SAMPLER_ADDRESS_MODE_REPEAT,
                                           true);
    ppSkyboxSampler = new cTextureSampler(pLogicalDevice,
                                          VK_FILTER_NEAREST,
                                          VK_SAMPLER_ADDRESS_MODE_REPEAT,
                                          false);


}

cTextureHandler::~cTextureHandler()
{
    // Delete all the textures
    for (auto&[sName, pTexture] : pmpTextures)
    {
        delete pTexture;
    }

    // Delete the texture samplers
    delete ppDefaultSampler;
    delete ppSkyboxSampler;
}

void cTextureHandler::LoadCallback(cTexture* pObject)
{
    pObject->LoadIntoRAM();
    pObject->CopyIntoGPU();
    pObject->UnloadFromRAM();
}

cTexture* cTextureHandler::LoadFromFile(const string& sFilePath, cTextureSampler* pSampler)
{
    // Try and find if this texture has already been loaded
    auto tResult = pmpTextures.find(sFilePath);
    if (tResult == pmpTextures.end())
    {
        // If not, create and load it
        cTexture* pTexture = new cTexture(ppLogicalDevice, sFilePath, pSampler);
        pmpTextures[sFilePath] = pTexture;
        LoadAsync(pTexture);
        return pTexture;
    } else
    {
        // If it's already loaded, just grab the loaded texture
        return tResult->second;
    }
}

cTexture* cTextureHandler::LoadFromFile(const string& sFilePath)
{
    return LoadFromFile(sFilePath, GetDefaultSampler());
}

cTextureSampler* cTextureHandler::GetDefaultSampler()
{
    return ppDefaultSampler;
}

cTextureSampler* cTextureHandler::GetSkyboxSampler()
{
    return ppSkyboxSampler;
}
