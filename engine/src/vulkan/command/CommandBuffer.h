#pragma once

#include <pch.h>
#include <vulkan/LogicalDevice.h>
#include <vulkan/swapchain/SwapChain.h>
#include <vulkan/command/CommandBufferRecorder.h>

class cCommandBuffer
{
private:
    cLogicalDevice* ppLogicalDevice;

    std::vector<VkCommandBuffer> paoCommandBuffers;

public:
    cCommandBuffer(cLogicalDevice* pLogicalDevice, cSwapChain* pSwapChain);
    ~cCommandBuffer();

    void RecordBuffers(iCommandBufferRecorder* pRecorder);

    VkCommandBuffer& GetBuffer(uint uiIndex);

private:
    void CreateBuffers(cSwapChain* pSwapChain);
    void RecordBuffer(VkCommandBuffer& oBuffer,
                      iCommandBufferRecorder* pRecorder,
                      VkCommandBufferBeginInfo& tBeginInfo,
                      uint uiIndex);
};
