#pragma once

#include <pch.h>
#include <vulkan/LogicalDevice.h>
#include <vulkan/uniform/UniformHandler.h>
#include <vulkan/swapchain/SwapChain.h>

class cMRTUniformHandler : public iUniformHandler
{
private:
    cLogicalDevice* ppLogicalDevice;
    cSwapChain* ppSwapChain;

    VkDescriptorSetLayout poObjectDescriptorSetLayout;
    VkDescriptorSetLayout poCameraDescriptorSetLayout;
    VkDescriptorSetLayout paoDescriptorSetLayouts[2];

    std::vector<VkBuffer> paoObjectUniformBuffers;
    std::vector<VkDeviceMemory> paoObjectUniformBuffersMemory;
    VkBuffer poCameraUniformBuffer = VK_NULL_HANDLE;
    VkDeviceMemory poCameraUniformBufferMemory = VK_NULL_HANDLE;

    VkDescriptorPool poDescriptorPool;
    std::vector<VkDescriptorSet> poObjectDescriptorSets;
    VkDescriptorSet poCameraDescriptorSet;

    VkDescriptorSet paoCurrentDescriptorSets[2];

public:
    cMRTUniformHandler(cLogicalDevice* pLogicalDevice, cSwapChain* pSwapChain);
    ~cMRTUniformHandler() override;

    void SetupUniformBuffers(cTextureHandler* pTextureHandler, cScene* pScene) override;
    void UpdateUniformBuffers(cScene* pScene) override;
    bool UpdateUniformTextures(cScene* pScene);

    uint GetDescriptorSetLayoutCount() override;
    VkDescriptorSetLayout* GetDescriptorSetLayouts() override;

    void CmdBindDescriptorSets(VkCommandBuffer& commandBuffer,
                               VkPipelineLayout& oPipelineLayout,
                               uint uiIndex) override;
    void RebuildUniforms() override;

private:
    void CreateUniformBuffers(cScene* pScene);
    void CreateDescriptorPool();
    void CreateDescriptorSets(cTextureHandler* pTextureHandler, cScene* pScene);

    void UpdateDescriptorTexture(uint uiIndex, cTexture* pTexture);

    void CopyToDeviceMemory(VkDeviceMemory& oDeviceMemory, void* pData, uint uiDataSize);
    void Cleanup();
};
