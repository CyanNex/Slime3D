#include <vulkan/renderpass/RenderPass.h>

cRenderPass::cRenderPass(cLogicalDevice* pLogicalDevice)
{
    assert(pLogicalDevice != nullptr);

    ppLogicalDevice = pLogicalDevice;
}

cRenderPass::~cRenderPass()
{
    if (poRenderPass != VK_NULL_HANDLE)
    {
        vkDestroyRenderPass(ppLogicalDevice->GetDevice(), poRenderPass, nullptr);
    }
}

VkRenderPass& cRenderPass::GetRenderPass()
{
    assert(poRenderPass != VK_NULL_HANDLE);

    return poRenderPass;
}
