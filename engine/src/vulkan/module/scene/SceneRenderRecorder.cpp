#include "SceneRenderRecorder.h"

cSceneRenderRecorder::cSceneRenderRecorder(cRenderPass* pRenderPass,
                                           cSwapChain* pSwapChain,
                                           cRenderPipeline* pGraphicsPipeline,
                                           iUniformHandler* pUniformHandler,
                                           cScene* pScene)
{
    ppRenderPass = pRenderPass;
    ppSwapChain = pSwapChain;
    ppGraphicsPipeline = pGraphicsPipeline;
    ppUniformHandler = pUniformHandler;
    ppScene = pScene;
}

void cSceneRenderRecorder::Setup(uint uiIndex)
{
    // Struct with information about our render pass
    ptRenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;

    // Set the render pass and framebuffer
    ptRenderPassInfo.renderPass = ppRenderPass->GetRenderPass();
    ptRenderPassInfo.framebuffer = ppSwapChain->GetFramebuffer(uiIndex);

    // Set the render area size
    ptRenderPassInfo.renderArea.offset = {0, 0};
    ptRenderPassInfo.renderArea.extent = ppSwapChain->ptSwapChainExtent;

    // Defines the clear color value to use
    paoClearValues[0].color = {0.0f, 0.3f, 0.5f, 1.0f}; // black with 100% opacity
    paoClearValues[1].depthStencil = {1.0f, 0}; // furthest possible depth
    ptRenderPassInfo.clearValueCount = (uint) paoClearValues.size();
    ptRenderPassInfo.pClearValues = paoClearValues.data();

}

void cSceneRenderRecorder::RecordCommands(VkCommandBuffer& oCommandBuffer, uint uiIndex)
{
    cGeometry* pGeometry;

    // Begin the render pass
    vkCmdBeginRenderPass(oCommandBuffer, &ptRenderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    // Bind the graphics pipeline
    vkCmdBindPipeline(oCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                      ppGraphicsPipeline->GetPipeline());

    // Bind the descriptor sets
    ppUniformHandler->CmdBindDescriptorSets(oCommandBuffer,
                                            ppGraphicsPipeline->GetLayout(),
                                            1);

    pGeometry = cViewportQuadGeometry::FULL_FRAME;
    pGeometry->CmdBindVertexBuffer(oCommandBuffer);
    pGeometry->CmdBindIndexBuffer(oCommandBuffer);
    vkCmdDrawIndexed(oCommandBuffer, pGeometry->GetIndexCount(), 1, 0, 0, 1);

    // Bind the descriptor sets
    ppUniformHandler->CmdBindDescriptorSets(oCommandBuffer,
                                            ppGraphicsPipeline->GetLayout(),
                                            0);

    pGeometry = cViewportQuadGeometry::HALF_FRAME;
    pGeometry->CmdBindVertexBuffer(oCommandBuffer);
    pGeometry->CmdBindIndexBuffer(oCommandBuffer);
    vkCmdDrawIndexed(oCommandBuffer, pGeometry->GetIndexCount(), 1, 0, 0, 1);

    // End the render pass
    vkCmdEndRenderPass(oCommandBuffer);
}
