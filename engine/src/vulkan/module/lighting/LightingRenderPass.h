#pragma once

#include <pch.h>
#include <vulkan/renderpass/RenderPass.h>
#include <vulkan/swapchain/SwapChain.h>

class cLightingRenderPass : public cRenderPass
{
public:
    cLightingRenderPass(cLogicalDevice* pLogicalDevice, cSwapChain* pSwapChain);

private:
    void GetColorAttachment(VkAttachmentDescription& tColorAttachment, cSwapChain* pSwapChain);
};
