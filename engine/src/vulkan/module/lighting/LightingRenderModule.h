#pragma once

#include <pch.h>
#include <vulkan/module/RenderModule.h>

class cLightingRenderModule : public cRenderModule
{
public:
    cLightingRenderModule(cLogicalDevice* pLogicalDevice,
                          cSwapChain* pSwapChain,
                          std::vector<string>& aShaders);
    ~cLightingRenderModule() override;

protected:
    void CreateUniformHandler() override;
    void CreateRenderPass() override;
    void CreatePipeline(std::vector<string>& aShaders) override;
};
