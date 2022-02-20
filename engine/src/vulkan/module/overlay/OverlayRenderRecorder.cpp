#include <vulkan/module/overlay/OverlayRenderRecorder.h>

cOverlayRenderRecorder::cOverlayRenderRecorder(cRenderPass* pRenderPass,
                                               cSwapChain* pSwapChain,
                                               cRenderPipeline* pGraphicsPipeline,
                                               iUniformHandler* pUniformHandler/*,
                                                             iGameManager* pOverlayProvider*/)
{
    ppRenderPass = pRenderPass;
    ppSwapChain = pSwapChain;
    ppPipeline = pGraphicsPipeline;
    ppUniformHandler = pUniformHandler;
//    ppOverlayProvider = pOverlayProvider;
}

void cOverlayRenderRecorder::Setup(uint uiIndex)
{
    // Struct with information about our render pass
    ptRenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;

    // Set the render pass and framebuffer
    ptRenderPassInfo.renderPass = ppRenderPass->GetRenderPass();
    ptRenderPassInfo.framebuffer = ppSwapChain->GetOverlayFramebuffer();

    // Set the render area size
    ptRenderPassInfo.renderArea.offset = {0, 0};
    ptRenderPassInfo.renderArea.extent = ppSwapChain->ptSwapChainExtent;

    // Defines the clear color value to use
    paoClearValues[0].color = {0.9f, 0.9f, 0.9f, 0.2f}; // black with 0% opacity
    ptRenderPassInfo.clearValueCount = (uint) paoClearValues.size();
    ptRenderPassInfo.pClearValues = paoClearValues.data();
}

void cOverlayRenderRecorder::RecordCommands(VkCommandBuffer& oCommandBuffer, uint uiIndex)
{
    // Begin the render pass
    vkCmdBeginRenderPass(oCommandBuffer, &ptRenderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    // Bind the graphics pipeline
    vkCmdBindPipeline(oCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                      ppPipeline->GetPipeline());

//    cOverlayWindow* pOverlayWindow = ppOverlayProvider->GetActiveOverlayWindow();
//    if (pOverlayWindow != nullptr)
//    {
//        cUIManager* pUIManager = pOverlayWindow->GetUIManager();
//        uint uiGeometryIndex = 0;
//        for (auto& tElement : pUIManager->patElements)
//        {
//            for (uint uiChildIndex = 0; uiChildIndex < tElement.ppElement->GetChildCount(); uiChildIndex++)
//            {
//                pUIManager->CmdBindVertexBuffer(oCommandBuffer, &tElement, uiChildIndex);
//
//                ppUniformHandler->CmdBindDescriptorSets(oCommandBuffer, ppPipeline->GetLayout(), uiGeometryIndex++);
//
//                uint uiVertexCount = tElement.ppElement->GetVertexCount(uiChildIndex);
//                vkCmdDraw(oCommandBuffer, uiVertexCount, 1, 0, 0);
//            }
//        }
//    }

    // End the render pass
    vkCmdEndRenderPass(oCommandBuffer);
}
