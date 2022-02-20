#pragma once

#include <pch.h>
#include <vulkan/LogicalDevice.h>
#include <vulkan/uniform/UniformHandler.h>
#include <vulkan/swapchain/SwapChain.h>

class cSceneUniformHandler : public iUniformHandler
{
private:
    cLogicalDevice* ppLogicalDevice;
    cSwapChain* ppSwapChain;

    VkDescriptorSetLayout poDescriptorSetLayout;

    VkBuffer poUniformBuffer;
    VkDeviceMemory poUniformBufferMemory;

    VkDescriptorPool poDescriptorPool = VK_NULL_HANDLE;
    VkDescriptorSet poDescriptorSets[2];

public:
    cSceneUniformHandler(cLogicalDevice* pLogicalDevice, cSwapChain* pSwapChain);
    ~cSceneUniformHandler() override;

    void SetupUniformBuffers(cTextureHandler* pTextureHandler, cScene* pScene) override;
    void UpdateUniformBuffers(cScene* pScene) override;

    uint GetDescriptorSetLayoutCount() override;
    VkDescriptorSetLayout* GetDescriptorSetLayouts() override;

    void CmdBindDescriptorSets(VkCommandBuffer& commandBuffer,
                               VkPipelineLayout& oPipelineLayout,
                               uint uiIndex) override;
    void RebuildUniforms() override;

private:
    void CreateUniformBuffers(cScene* pScene);
    void CreateDescriptorPool();
    void CreateDescriptorSet(VkDescriptorSet* pDescriptorSet, tFrameBufferAttachment* tAttachment);
    void CreateDescriptorSets(cTextureHandler* pTextureHandler, cScene* pScene);
    void Cleanup();
};
