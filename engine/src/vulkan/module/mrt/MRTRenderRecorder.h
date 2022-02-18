#pragma once

#include <pch.h>
#include <vulkan/command/CommandBufferRecorder.h>
#include <vulkan/pipeline/RenderPipeline.h>

class cMRTRenderRecorder : public iCommandBufferRecorder
{
private:
    cRenderPass* ppRenderPass;
    cSwapChain* ppSwapChain;
    cRenderPipeline* ppGraphicsPipeline;
    iUniformHandler* ppUniformHandler;
    cScene* ppScene;

    VkRenderPassBeginInfo ptRenderPassInfo = {};
    std::array<VkClearValue, 5> paoClearValues = {};

public:
    cMRTRenderRecorder(cRenderPass* pRenderPass,
                       cSwapChain* pSwapChain,
                       cRenderPipeline* pGraphicsPipeline,
                       iUniformHandler* pUniformHandler,
                       cScene* pScene);

    void Setup(uint uiIndex) override;
    void RecordCommands(VkCommandBuffer& oCommandBuffer, uint uiIndex) override;
};
