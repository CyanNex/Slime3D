#include <vulkan/module/RenderModule.h>

cRenderModule::cRenderModule(cLogicalDevice* pLogicalDevice, cSwapChain* pSwapChain, std::vector<string>& aShaders)
        : paShaders(aShaders)
{
    assert(pLogicalDevice != nullptr);
    assert(pSwapChain != nullptr);

    ppLogicalDevice = pLogicalDevice;
    ppSwapChain = pSwapChain;
}

void cRenderModule::Init()
{
    CreateUniformHandler();
    assert(ppUniformHandler != nullptr); // uniform handler should be created

    CreateRenderPass();
    assert(ppRenderPass != nullptr); // render pass should be created

    CreatePipeline(paShaders);
    assert(ppRenderPipeline != nullptr); // pipeline should be created

    ENGINE_LOG("Render module '" << CURRENT_CLASS_NAME << "' initialized");
}

cRenderModule::~cRenderModule()
{
    delete ppRenderPipeline;
    delete ppRenderPass;
    delete ppUniformHandler;
}

iUniformHandler* cRenderModule::GetUniformHandler()
{
    assert(ppUniformHandler != nullptr);

    return ppUniformHandler;
}

cRenderPass* cRenderModule::GetRenderPass()
{
    assert(ppRenderPass != nullptr);

    return ppRenderPass;
}

cRenderPipeline* cRenderModule::GetRenderPipeline()
{
    assert(ppRenderPipeline != nullptr);

    return ppRenderPipeline;
}

void cRenderModule::RebuildRenderPass()
{
    delete ppRenderPass;
    ppRenderPass = nullptr;
    CreateRenderPass();
    assert(ppRenderPass != nullptr);
    assert(ppRenderPass->GetRenderPass() != VK_NULL_HANDLE);
}
