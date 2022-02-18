#pragma once

#include <pch.h>
#include <vulkan/renderpass/RenderPass.h>
#include <vulkan/swapchain/SwapChain.h>

class cOverlayRenderPass : public cRenderPass
{
private:
    cSwapChain* ppSwapChain;

public:
    cOverlayRenderPass(cLogicalDevice* pLogicalDevice, cSwapChain* pSwapChain);

protected:
    void CreateRenderPass();
};
