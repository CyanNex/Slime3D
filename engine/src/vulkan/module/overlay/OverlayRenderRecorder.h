#pragma once

#include <pch.h>
#include <vulkan/command/CommandBufferRecorder.h>
#include <vulkan/pipeline/RenderPipeline.h>

class cOverlayRenderRecorder : public iCommandBufferRecorder
{
private:
    cRenderPass* ppRenderPass;
    cSwapChain* ppSwapChain;
    cRenderPipeline* ppPipeline;
    iUniformHandler* ppUniformHandler;

    VkRenderPassBeginInfo ptRenderPassInfo = {};
    std::array<VkClearValue, 1> paoClearValues = {};

//    iGameManager* ppOverlayProvider;

public:
    cOverlayRenderRecorder(cRenderPass* pRenderPass,
                           cSwapChain* pSwapChain,
                           cRenderPipeline* pGraphicsPipeline,
                           iUniformHandler* pUniformHandler/*,
                                  iGameManager* pOverlayProvider*/);

    void Setup(uint uiIndex) override;
    void RecordCommands(VkCommandBuffer& oCommandBuffer, uint uiIndex) override;
};
