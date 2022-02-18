#pragma once

#include <pch.h>
#include <vulkan/renderpass/RenderPass.h>
#include <vulkan/swapchain/SwapChain.h>

class cMRTRenderPass : public cRenderPass
{
private:
    cSwapChain* ppSwapChain;

public:
    cMRTRenderPass(cLogicalDevice* pLogicalDevice, cSwapChain* pSwapChain);

protected:
    void CreateRenderPass();
};
