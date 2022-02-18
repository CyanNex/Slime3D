#pragma once

#include <pch.h>
#include <vulkan/LogicalDevice.h>
#include <vulkan/pipeline/RenderPipeline.h>

class cLightingPipeline : public cRenderPipeline
{
public:
    cLightingPipeline(cSwapChain* pSwapChain,
                      cLogicalDevice* pLogicalDevice,
                      cRenderPass* pRenderPass,
                      iUniformHandler* pUniformHandler,
                      std::vector<string>& aShaders);

protected:
    void CreatePipelineLayout(cSwapChain* pSwapChain,
                              cLogicalDevice* pLogicalDevice,
                              cRenderPass* pRenderPass,
                              iUniformHandler* pUniformHandler) override;
    void CreatePipeline(cSwapChain* pSwapChain,
                        cLogicalDevice* pLogicalDevice,
                        cRenderPass* pRenderPass,
                        iUniformHandler* pUniformHandler,
                        std::vector<string>& aShaders) override;
};
