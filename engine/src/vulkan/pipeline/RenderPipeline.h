#pragma once

#include <pch.h>
#include <vulkan/LogicalDevice.h>
#include <vulkan/swapchain/SwapChain.h>
#include <vulkan/renderpass/RenderPass.h>
#include <vulkan/uniform/UniformHandler.h>

class cRenderPipeline
{
protected:
    VkPipelineLayout poPipelineLayout = VK_NULL_HANDLE;
    VkPipeline poPipeline = VK_NULL_HANDLE;

    cLogicalDevice* ppLogicalDevice;
    cSwapChain* ppSwapChain;
    cRenderPass* ppRenderPass;
    iUniformHandler* ppUniformHandler;
    std::vector<string> paShaders;

public:
    virtual ~cRenderPipeline();

    VkPipelineLayout& GetLayout();
    VkPipeline& GetPipeline();

    void RebuildPipeline(cRenderPass* pRenderPass);

protected:
    void Init(cSwapChain* pSwapChain,
              cLogicalDevice* pLogicalDevice,
              cRenderPass* pRenderPass,
              iUniformHandler* pUniformHandler,
              std::vector<string>& aShaders);

    virtual void CreatePipelineLayout(cSwapChain* pSwapChain,
                                      cLogicalDevice* pLogicalDevice,
                                      cRenderPass* pRenderPass,
                                      iUniformHandler* pUniformHandler) = 0;
    virtual void CreatePipeline(cSwapChain* pSwapChain,
                                cLogicalDevice* pLogicalDevice,
                                cRenderPass* pRenderPass,
                                iUniformHandler* pUniformHandler,
                                std::vector<string>& aShaders) = 0;

private:
    void Cleanup();
};
