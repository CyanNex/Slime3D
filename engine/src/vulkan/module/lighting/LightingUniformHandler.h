#pragma once

#include <pch.h>
#include <vulkan/LogicalDevice.h>
#include <vulkan/uniform/UniformHandler.h>
#include <vulkan/swapchain/SwapChain.h>

enum eLightingMode
{
    FAST_LIGHTING, FANCY_LIGHTING
};

class cLightingUniformHandler : public iUniformHandler
{
public:
    static float pfGamma;
    static eLightingMode peLightingMode;

private:
    cLogicalDevice* ppLogicalDevice;
    cSwapChain* ppSwapChain;

    VkDescriptorSetLayout poDescriptorSetLayout;

    VkBuffer poUniformBuffer;
    VkDeviceMemory poUniformBufferMemory;

    VkDescriptorPool poDescriptorPool;
    VkDescriptorSet poDescriptorSet;

    uint puiLightsCount;
    size_t puiLightsMemorySize;

public:
    cLightingUniformHandler(cLogicalDevice* pLogicalDevice, cSwapChain* pSwapChain);
    ~cLightingUniformHandler() override;

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
    void CreateDescriptorSets(cTextureHandler* pTextureHandler, cScene* pScene);
    void Cleanup();
};;
