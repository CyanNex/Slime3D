#include <vulkan/module/scene/SceneRenderModule.h>
#include <vulkan/module/scene/SceneUniformHandler.h>
#include <vulkan/module/scene/SceneRenderPass.h>
#include <vulkan/module/lighting/LightingPipeline.h>

cSceneRenderModule::cSceneRenderModule(cLogicalDevice* pLogicalDevice, cSwapChain* pSwapChain,
                                       std::vector<string>& aShaders) : cRenderModule(pLogicalDevice, pSwapChain,
                                                                                      aShaders)
{
    Init();
}

cSceneRenderModule::~cSceneRenderModule()
{
}

void cSceneRenderModule::CreateUniformHandler()
{
    // Create the uniform handler. This is responsible for the uniform variables
    ppUniformHandler = new cSceneUniformHandler(ppLogicalDevice, ppSwapChain);
}

void cSceneRenderModule::CreateRenderPass()
{
    // Create the render pass. This holds information about the frames we want to render.
    // will probably be moved somewhere else later
    ppRenderPass = new cSceneRenderPass(ppLogicalDevice, ppSwapChain);
}

void cSceneRenderModule::CreatePipeline(std::vector<string>& aShaders)
{
    // Create the graphics pipeline. Handles the shaders and fixed-function operations for the graphics pipeline.
    ppRenderPipeline = new cLightingPipeline(ppSwapChain, ppLogicalDevice, ppRenderPass, ppUniformHandler, aShaders);
}
