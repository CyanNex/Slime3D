#pragma once

#include <pch.h>
#include <vulkan/renderpass/RenderPass.h>
#include <vulkan/swapchain/SwapChain.h>

class cSceneRenderPass : public cRenderPass
{
public:
    cSceneRenderPass(cLogicalDevice* pLogicalDevice, cSwapChain* pSwapChain);

private:
    static void GetColorAttachment(VkAttachmentDescription& tColorAttachment, cSwapChain* pSwapChain);
};
