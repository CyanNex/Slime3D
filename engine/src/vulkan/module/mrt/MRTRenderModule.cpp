#include <vulkan/module/mrt/MRTRenderModule.h>
#include <vulkan/module/mrt/MRTUniformHandler.h>
#include <vulkan/module/mrt/MRTRenderPass.h>
#include <vulkan/module/mrt/MRTPipeline.h>

cMRTRenderModule::cMRTRenderModule(cLogicalDevice* pLogicalDevice,
                                   cSwapChain* pSwapChain,
                                   std::vector<string>& aShaders)
        : cRenderModule(pLogicalDevice, pSwapChain, aShaders)
{
    Init();
}

void cMRTRenderModule::CreateUniformHandler()
{
    // Create the uniform handler. This is responsible for the uniform variables
    ppUniformHandler = new cMRTUniformHandler(ppLogicalDevice, ppSwapChain);
}

void cMRTRenderModule::CreateRenderPass()
{
    // Create the render pass. This holds information about the frames we want to render.
    // will probably be moved somewhere else later
    ppRenderPass = new cMRTRenderPass(ppLogicalDevice, ppSwapChain);
}

void cMRTRenderModule::CreatePipeline(std::vector<string>& aShaders)
{
    // Create the graphics pipeline. Handles the shaders and fixed-function operations for the graphics pipeline.
    ppRenderPipeline = new cMRTPipeline(ppSwapChain, ppLogicalDevice, ppRenderPass, ppUniformHandler, aShaders);
}
