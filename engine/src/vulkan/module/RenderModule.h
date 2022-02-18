#pragma once

#include <pch.h>
#include <vulkan/renderpass/RenderPass.h>
#include <vulkan/pipeline/RenderPipeline.h>
#include <vulkan/uniform/UniformHandler.h>
#include <vulkan/command/CommandBufferRecorder.h>

class cRenderModule
{
protected:
    iUniformHandler* ppUniformHandler = nullptr;
    cRenderPass* ppRenderPass = nullptr;
    cRenderPipeline* ppRenderPipeline = nullptr;

    cLogicalDevice* ppLogicalDevice = nullptr;
    cSwapChain* ppSwapChain = nullptr;

    std::vector<string>& paShaders;

public:
    cRenderModule(cLogicalDevice* pLogicalDevice, cSwapChain* pSwapChain, std::vector<string>& aShaders);
    virtual ~cRenderModule();

    iUniformHandler* GetUniformHandler();
    cRenderPass* GetRenderPass();
    cRenderPipeline* GetRenderPipeline();

    void RebuildRenderPass();

protected:
    void Init();

    // Create the uniform handler. This is responsible for the uniform variables
    virtual void CreateUniformHandler() = 0;
    // Create the render pass. This holds information about the frames we want to render.
    virtual void CreateRenderPass() = 0;
    // Create the graphics pipeline. Handles the shaders and fixed-function operations for the graphics pipeline.
    virtual void CreatePipeline(std::vector<string>& aShaders) = 0;
};
