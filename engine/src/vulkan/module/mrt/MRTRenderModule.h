#pragma once

#include <pch.h>
#include <vulkan/module/RenderModule.h>

class cMRTRenderModule : public cRenderModule
{
public:
    cMRTRenderModule(cLogicalDevice* pLogicalDevice,
                     cSwapChain* pSwapChain,
                     std::vector<string>& aShaders);

protected:
    void CreateUniformHandler() override;
    void CreateRenderPass() override;
    void CreatePipeline(std::vector<string>& aShaders) override;
};
