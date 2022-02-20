#pragma once

#include <pch.h>
#include <vulkan/module/RenderModule.h>

class cSceneRenderModule : public cRenderModule
{
public:
    cSceneRenderModule(cLogicalDevice* pLogicalDevice,
                          cSwapChain* pSwapChain,
                          std::vector<string>& aShaders);
    ~cSceneRenderModule() override;

protected:
    void CreateUniformHandler() override;
    void CreateRenderPass() override;
    void CreatePipeline(std::vector<string>& aShaders) override;
};
