#pragma once

#include <pch.h>
#include <vulkan/swapchain/SwapChain.h>
#include <vulkan/command/CommandBufferRecorder.h>
#include <vulkan/renderpass/RenderPass.h>

class cClearScreenRecorder : public iCommandBufferRecorder
{
private:
    cRenderPass* ppRenderPass;
    cSwapChain* ppSwapChain;

    VkRenderPassBeginInfo ptRenderPassInfo = {};
    std::array<VkClearValue, 2> paoClearValues = {};

public:
    cClearScreenRecorder(cRenderPass* pRenderPass,
                         cSwapChain* pSwapChain);

    void Setup(uint uiIndex) override;
    void RecordCommands(VkCommandBuffer& oCommandBuffer, uint uiIndex) override;
};
