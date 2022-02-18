#include <vulkan/pipeline/RenderPipeline.h>

void cRenderPipeline::Init(cSwapChain* pSwapChain,
                           cLogicalDevice* pLogicalDevice,
                           cRenderPass* pRenderPass,
                           iUniformHandler* pUniformHandler,
                           std::vector<string>& aShaders)
{
    assert(pSwapChain != nullptr);
    assert(pLogicalDevice != nullptr);
    assert(pRenderPass != nullptr);
    assert(pUniformHandler != nullptr);
    assert(aShaders.size() >= 2);

    ppLogicalDevice = pLogicalDevice;
    ppSwapChain = pSwapChain;
    ppRenderPass = pRenderPass;
    ppUniformHandler = pUniformHandler;
    paShaders = aShaders;

    CreatePipelineLayout(pSwapChain, pLogicalDevice, pRenderPass, pUniformHandler);
    assert(poPipelineLayout != VK_NULL_HANDLE); // pipeline layout should be created

    CreatePipeline(pSwapChain, pLogicalDevice, pRenderPass, pUniformHandler, aShaders);
    assert(poPipeline != VK_NULL_HANDLE); // pipeline should be created

    ENGINE_LOG("Render pipeline '" << CURRENT_CLASS_NAME << "' initialized");
}

cRenderPipeline::~cRenderPipeline()
{
    Cleanup();
    if (poPipelineLayout != VK_NULL_HANDLE)
    {
        ppLogicalDevice->DestroyPipelineLayout(poPipelineLayout, nullptr);
    }
}

VkPipelineLayout& cRenderPipeline::GetLayout()
{
    assert(poPipelineLayout != VK_NULL_HANDLE); // render pipeline needs to be initialized first

    return poPipelineLayout;
}

VkPipeline& cRenderPipeline::GetPipeline()
{
    assert(poPipeline != VK_NULL_HANDLE); // render pipeline needs to be initialized first

    return poPipeline;
}

void cRenderPipeline::Cleanup()
{
    if (poPipeline != VK_NULL_HANDLE)
    {
        ppLogicalDevice->DestroyPipeline(poPipeline, nullptr);
        poPipeline = VK_NULL_HANDLE;
    }
}

void cRenderPipeline::RebuildPipeline(cRenderPass* pRenderPass)
{
    ppRenderPass = pRenderPass;
    Cleanup();
    CreatePipeline(ppSwapChain, ppLogicalDevice, pRenderPass,
                   ppUniformHandler, paShaders);
}
