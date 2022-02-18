#pragma once

#include <pch.h>
#include <vulkan/LogicalDevice.h>
#include <vulkan/uniform/UniformHandler.h>
#include <vulkan/swapchain/SwapChain.h>
#include <vulkan/module/overlay/element/Font.h>

class cOverlayUniformHandler : public iUniformHandler
{
private:
    cLogicalDevice* ppLogicalDevice;

    cFont* ppFont;
    cWindow* ppWindow;

    VkDescriptorSetLayout poDescriptorSetLayout;
    VkDescriptorSetLayout poElementDescriptorSetLayout;
    VkDescriptorSetLayout paoDescriptorSetLayouts[2];

    VkBuffer poBuffer;
    VkDeviceMemory poBufferMemory;
    std::vector<VkBuffer> paoElementUniformBuffers;
    std::vector<VkDeviceMemory> paoElementUniformBuffersMemory;

    VkDescriptorPool poDescriptorPool;
    VkDescriptorSet poDescriptorSet;
    std::vector<VkDescriptorSet> paoElementDescriptorSets;

    VkDescriptorSet paoCurrentDescriptorSets[2];

//    iGameManager* ppOverlayProvider;

    bool pbAllocated = false;

public:
    cOverlayUniformHandler(cLogicalDevice* pLogicalDevice,
                           cFont* pFont, cWindow* pWindow/*,
                           iGameManager* pOverlayProvider*/);
    ~cOverlayUniformHandler();

    void SetupUniformBuffers(cTextureHandler* pTextureHandler, cScene* pScene) override;
    void UpdateUniformBuffers(cScene* pScene) override;

    uint GetDescriptorSetLayoutCount() override;
    VkDescriptorSetLayout* GetDescriptorSetLayouts() override;

    void CmdBindDescriptorSets(VkCommandBuffer& commandBuffer,
                               VkPipelineLayout& oPipelineLayout,
                               uint uiIndex) override;
    void RebuildUniforms() override;

private:
    void Cleanup();
    void CreateUniformBuffers();
    void CreateDescriptorPool();
    void CreateDescriptorSet();

    void CopyToDeviceMemory(VkDeviceMemory& oDeviceMemory, void* pData, uint uiDataSize);
};
