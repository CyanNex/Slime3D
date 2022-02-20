#pragma once

#include <pch.h>
#include <vulkan/command/CommandBufferRecorder.h>
#include <vulkan/pipeline/RenderPipeline.h>

class cSceneRenderRecorder : public iCommandBufferRecorder
{
private:
    cRenderPass* ppRenderPass;
    cSwapChain* ppSwapChain;
    cRenderPipeline* ppGraphicsPipeline;
    iUniformHandler* ppUniformHandler;
    cScene* ppScene;

    VkRenderPassBeginInfo ptRenderPassInfo = {};
    std::array<VkClearValue, 2> paoClearValues = {};

public:
    cSceneRenderRecorder(cRenderPass* pRenderPass,
                            cSwapChain* pSwapChain,
                            cRenderPipeline* pGraphicsPipeline,
                            iUniformHandler* pUniformHandler,
                            cScene* pScene);

    void Setup(uint uiIndex) override;
    void RecordCommands(VkCommandBuffer& oCommandBuffer, uint uiIndex) override;
};
