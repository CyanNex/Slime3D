#include <vulkan/module/scene/SceneUniformHandler.h>
#include <vulkan/util/BufferHelper.h>
#include <util/UtilFunctions.h>

cSceneUniformHandler::cSceneUniformHandler(cLogicalDevice* pLogicalDevice, cSwapChain* pSwapChain)
{
    ppLogicalDevice = pLogicalDevice;
    ppSwapChain = pSwapChain;

    std::array<VkDescriptorSetLayoutBinding, 2> atLayoutBindings{};

    atLayoutBindings[0].binding = 0;
    atLayoutBindings[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    atLayoutBindings[0].descriptorCount = 1;
    atLayoutBindings[0].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    atLayoutBindings[0].pImmutableSamplers = nullptr;

    atLayoutBindings[1].binding = 1;
    atLayoutBindings[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    atLayoutBindings[1].descriptorCount = 1;
    atLayoutBindings[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    atLayoutBindings[1].pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutCreateInfo tCameraLayoutInfo = {};
    tCameraLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    tCameraLayoutInfo.bindingCount = (uint) atLayoutBindings.size();
    tCameraLayoutInfo.pBindings = atLayoutBindings.data();

    if (!pLogicalDevice->CreateDescriptorSetLayout(&tCameraLayoutInfo, nullptr, &poDescriptorSetLayout))
    {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}

cSceneUniformHandler::~cSceneUniformHandler()
{
    ppLogicalDevice->DestroyDescriptorSetLayout(poDescriptorSetLayout, nullptr);

    Cleanup();
}

void cSceneUniformHandler::SetupUniformBuffers(cTextureHandler* pTextureHandler, cScene* pScene)
{
    CreateUniformBuffers(pScene);
    CreateDescriptorPool();
    CreateDescriptorSets(pTextureHandler, pScene);
}

void cSceneUniformHandler::CreateUniformBuffers(cScene* pScene)
{
    cBufferHelper::CreateBuffer(ppLogicalDevice, 32,
                                VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
                                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                poUniformBuffer, poUniformBufferMemory);
}

void cSceneUniformHandler::UpdateUniformBuffers(cScene* pScene)
{
}

void cSceneUniformHandler::CreateDescriptorPool()
{
    std::array<VkDescriptorPoolSize, 2> atPoolSizes = {};
    atPoolSizes[0].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    atPoolSizes[0].descriptorCount = 2;
    atPoolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    atPoolSizes[1].descriptorCount = 2;

    VkDescriptorPoolCreateInfo tPoolInfo = {};
    tPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    tPoolInfo.poolSizeCount = (uint) atPoolSizes.size();
    tPoolInfo.pPoolSizes = atPoolSizes.data();

    tPoolInfo.maxSets = 2;

    if (!ppLogicalDevice->CreateDescriptorPool(&tPoolInfo, nullptr, &poDescriptorPool))
    {
        throw std::runtime_error("failed to create descriptor pool!");
    }
}

void cSceneUniformHandler::CreateDescriptorSets(cTextureHandler* pTextureHandler, cScene* pScene)
{
    VkDescriptorSetAllocateInfo tAllocateInfo = {};
    tAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;

    VkDescriptorSetLayout layouts[2] = {
            poDescriptorSetLayout, poDescriptorSetLayout
    };

    tAllocateInfo.descriptorPool = poDescriptorPool;
    tAllocateInfo.descriptorSetCount = 2;
    tAllocateInfo.pSetLayouts = layouts;

    if (!ppLogicalDevice->AllocateDescriptorSets(&tAllocateInfo, poDescriptorSets))
    {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }

    CreateDescriptorSet(&poDescriptorSets[0], &ppSwapChain->GetSceneAttachment());
    CreateDescriptorSet(&poDescriptorSets[1], &ppSwapChain->GetOverlayAttachment());
}

void cSceneUniformHandler::CreateDescriptorSet(VkDescriptorSet* pDescriptorSet, tFrameBufferAttachment* tAttachment)
{
    VkDescriptorBufferInfo tBufferInfo = {};
    tBufferInfo.buffer = poUniformBuffer;
    tBufferInfo.offset = 0;
    tBufferInfo.range = VK_WHOLE_SIZE;

    VkDescriptorImageInfo tImageInfo = {};
    tImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    tImageInfo.imageView = tAttachment->oView;
    tImageInfo.sampler = ppSwapChain->GetSampler();

    std::array<VkWriteDescriptorSet, 2> atDescriptorWrites = {};

    atDescriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    atDescriptorWrites[0].dstSet = *pDescriptorSet;
    atDescriptorWrites[0].dstBinding = 0;
    atDescriptorWrites[0].dstArrayElement = 0;
    atDescriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    atDescriptorWrites[0].descriptorCount = 1;
    atDescriptorWrites[0].pBufferInfo = &tBufferInfo;

    atDescriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    atDescriptorWrites[1].dstSet = *pDescriptorSet;
    atDescriptorWrites[1].dstBinding = 1;
    atDescriptorWrites[1].dstArrayElement = 0;
    atDescriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    atDescriptorWrites[1].descriptorCount = 1;
    atDescriptorWrites[1].pImageInfo = &tImageInfo;

    ppLogicalDevice->UpdateDescriptorSets((uint) atDescriptorWrites.size(), atDescriptorWrites.data(),
                                          0, nullptr);
}

uint cSceneUniformHandler::GetDescriptorSetLayoutCount()
{
    return 1;
}

VkDescriptorSetLayout* cSceneUniformHandler::GetDescriptorSetLayouts()
{
    return &poDescriptorSetLayout;
}

void cSceneUniformHandler::CmdBindDescriptorSets(VkCommandBuffer& commandBuffer,
                                                 VkPipelineLayout& oPipelineLayout,
                                                 uint uiIndex)
{
    vkCmdBindDescriptorSets(commandBuffer,
                            VK_PIPELINE_BIND_POINT_GRAPHICS,
                            oPipelineLayout, 0,
                            1, &poDescriptorSets[uiIndex],
                            0, nullptr);
}

void cSceneUniformHandler::RebuildUniforms()
{
    Cleanup();
}

void cSceneUniformHandler::Cleanup()
{
    ppLogicalDevice->DestroyBuffer(poUniformBuffer, nullptr);
    ppLogicalDevice->FreeMemory(poUniformBufferMemory, nullptr);

    ppLogicalDevice->DestroyDescriptorPool(poDescriptorPool, nullptr);
}
