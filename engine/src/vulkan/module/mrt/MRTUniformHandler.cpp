#include <vulkan/module/mrt/MRTUniformHandler.h>
#include <vulkan/util/BufferHelper.h>

struct tObjectUniformData
{
    glm::mat4 tModel;
    bool bLighting;
};

struct tCameraUniformData
{
    glm::mat4 tView;
    glm::mat4 tProjection;
};

cMRTUniformHandler::cMRTUniformHandler(cLogicalDevice* pLogicalDevice,
                                       cSwapChain* pSwapChain)
{
    ppLogicalDevice = pLogicalDevice;
    ppSwapChain = pSwapChain;

    // Binding for the uniform data for every object
    VkDescriptorSetLayoutBinding tUBOLayoutBinding = {};
    tUBOLayoutBinding.binding = 0;
    tUBOLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    tUBOLayoutBinding.descriptorCount = 1;
    tUBOLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    tUBOLayoutBinding.pImmutableSamplers = nullptr;

    // Binding for the texture sampler
    VkDescriptorSetLayoutBinding tSamplerLayoutBinding = {};
    tSamplerLayoutBinding.binding = 1;
    tSamplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    tSamplerLayoutBinding.descriptorCount = 1;
    tSamplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    tSamplerLayoutBinding.pImmutableSamplers = nullptr;

    // Binding for the texture sampler
    VkDescriptorSetLayoutBinding tMaterialLayoutBinding = {};
    tMaterialLayoutBinding.binding = 2;
    tMaterialLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    tMaterialLayoutBinding.descriptorCount = 1;
    tMaterialLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    tMaterialLayoutBinding.pImmutableSamplers = nullptr;

    std::array<VkDescriptorSetLayoutBinding, 3> atBindings = {tUBOLayoutBinding, tSamplerLayoutBinding,
                                                              tMaterialLayoutBinding};
    VkDescriptorSetLayoutCreateInfo tLayoutInfo = {};
    tLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    tLayoutInfo.bindingCount = (uint) atBindings.size();
    tLayoutInfo.pBindings = atBindings.data();

    if (!pLogicalDevice->CreateDescriptorSetLayout(&tLayoutInfo, nullptr, &poObjectDescriptorSetLayout))
    {
        throw std::runtime_error("failed to create descriptor set layout!");
    }

    VkDescriptorSetLayoutBinding tCameraLayoutBinding = {};
    tCameraLayoutBinding.binding = 0;
    tCameraLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    tCameraLayoutBinding.descriptorCount = 1;
    tCameraLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    tCameraLayoutBinding.pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutCreateInfo tCameraLayoutInfo = {};
    tCameraLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    tCameraLayoutInfo.bindingCount = 1;
    tCameraLayoutInfo.pBindings = &tCameraLayoutBinding;

    if (!pLogicalDevice->CreateDescriptorSetLayout(&tCameraLayoutInfo, nullptr, &poCameraDescriptorSetLayout))
    {
        throw std::runtime_error("failed to create descriptor set layout!");
    }

    paoDescriptorSetLayouts[0] = poObjectDescriptorSetLayout;
    paoDescriptorSetLayouts[1] = poCameraDescriptorSetLayout;
}


cMRTUniformHandler::~cMRTUniformHandler()
{
    ppLogicalDevice->DestroyDescriptorSetLayout(poObjectDescriptorSetLayout, nullptr);
    ppLogicalDevice->DestroyDescriptorSetLayout(poCameraDescriptorSetLayout, nullptr);

    Cleanup();
}

void cMRTUniformHandler::SetupUniformBuffers(cTextureHandler* pTextureHandler,
                                             cScene* pScene)
{
    CreateUniformBuffers(pScene);
    CreateDescriptorPool();
    CreateDescriptorSets(pTextureHandler, pScene);
}

void cMRTUniformHandler::CreateUniformBuffers(cScene* pScene)
{
    VkDeviceSize bufferSize = sizeof(tObjectUniformData);
    uint uiCount = pScene->GetObjectCount();

    // Create a buffer for every object in the scene
    paoObjectUniformBuffers.resize(uiCount);
    paoObjectUniformBuffersMemory.resize(uiCount);
    for (uint i = 0; i < uiCount; i++)
    {
        cBufferHelper::CreateBuffer(ppLogicalDevice, bufferSize,
                                    VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                    paoObjectUniformBuffers[i], paoObjectUniformBuffersMemory[i]);
    }

    cBufferHelper::CreateBuffer(ppLogicalDevice, sizeof(tCameraUniformData),
                                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                poCameraUniformBuffer, poCameraUniformBufferMemory);

    // Load all the object uniforms into memory
    uint uiIndex = 0;
    for (auto oObject : pScene->GetObjects())
    {
        oObject.second->puiUniformIndex = uiIndex;
        oObject.second->pbLoaded = true;

        // Struct with uniforms for the object
        tObjectUniformData tObjectData = {};

        tObjectData.bLighting = oObject.second->pbLighting;

        // Set the model matrix of the object
        tObjectData.tModel = oObject.second->GetModelMatrix();

        // Copy the data to memory
        CopyToDeviceMemory(paoObjectUniformBuffersMemory[uiIndex++], &tObjectData, sizeof(tObjectData));
    }
}

void cMRTUniformHandler::UpdateUniformBuffers(cScene* pScene)
{
    // We don't want to do anything before the scene is loaded
    if (pScene == nullptr) return;

    // Get the camera and screen extent
    cCamera* pCamera = &pScene->GetCamera();
    VkExtent2D tExtent = ppSwapChain->ptSwapChainExtent;

#ifdef ENGINE_TIMING_DEBUG
    steady_clock::time_point tStartTime = steady_clock::now();
#endif

    // Struct with uniforms for the camera
    tCameraUniformData tCameraData = {};

    // Set the view matrix of the camera
    tCameraData.tView = pScene->GetCamera().GetViewMatrix();

    // Set the projection matrix
    // TODO: We don't have to recalculate this every frame
    tCameraData.tProjection = glm::perspective(
            glm::radians(pCamera->fFoV),
            tExtent.width / (float) tExtent.height,
            pCamera->fZNear, pCamera->fZFar);
    tCameraData.tProjection[1][1] *= -1; // invert the Y axis

    // Copy the data to memory
    CopyToDeviceMemory(poCameraUniformBufferMemory, &tCameraData, sizeof(tCameraData));

    // Update the uniforms for all movable objects
    for (auto oObject : pScene->GetMovableObjects())
    {
        // Struct with uniforms for the object
        tObjectUniformData tObjectData = {};

        tObjectData.bLighting = oObject->pbLighting && oObject->pbVisible;

        // Set the model matrix of the object
        tObjectData.tModel = oObject->GetModelMatrix();

        // Copy the data to memory
        CopyToDeviceMemory(paoObjectUniformBuffersMemory[oObject->puiUniformIndex], &tObjectData,
                           sizeof(tObjectData));
    }

#ifdef ENGINE_TIMING_DEBUG
    ENGINE_LOG("mrt ubo copy took " << duration_cast<microseconds>(steady_clock::now() - tStartTime).count()
                                    << "us on the CPU");
#endif
}

bool cMRTUniformHandler::UpdateUniformTextures(cScene* pScene)
{
    uint uiIndex = 0;
    bool bIdle = false;
    for (auto&[sName, pObject] : pScene->GetObjects())
    {
        if (pObject->GetMesh()->Invalidated())
        {
            if (!bIdle)
            {
                bIdle = true;
                ppLogicalDevice->WaitUntilIdle();
            }

            cMesh* pMesh = pObject->GetMesh();
            UpdateDescriptorTexture(uiIndex, pMesh->GetTexture());
            pMesh->Validate();
        }
        uiIndex++;
    }

    return bIdle;
}

void cMRTUniformHandler::CopyToDeviceMemory(VkDeviceMemory& oDeviceMemory, void* pData, uint uiDataSize)
{
    void* pMappedMemory;
    ppLogicalDevice->MapMemory(oDeviceMemory, 0, uiDataSize, 0, &pMappedMemory);
    {
        memcpy(pMappedMemory, pData, uiDataSize);
    }
    ppLogicalDevice->UnmapMemory(oDeviceMemory);
}

void cMRTUniformHandler::CreateDescriptorPool()
{
    std::array<VkDescriptorPoolSize, 4> atPoolSizes = {};
    atPoolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    atPoolSizes[0].descriptorCount = 1;
    if (paoObjectUniformBuffers.size() > 0)
    {
        atPoolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        atPoolSizes[1].descriptorCount = (uint) paoObjectUniformBuffers.size();
        atPoolSizes[2].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        atPoolSizes[2].descriptorCount = (uint) paoObjectUniformBuffers.size();
        atPoolSizes[3].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        atPoolSizes[3].descriptorCount = (uint) paoObjectUniformBuffers.size();
    }

    VkDescriptorPoolCreateInfo tPoolInfo = {};
    tPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    tPoolInfo.poolSizeCount = paoObjectUniformBuffers.size() > 0 ? 4 : 1;
    tPoolInfo.pPoolSizes = atPoolSizes.data();

    tPoolInfo.maxSets = (uint) paoObjectUniformBuffers.size() + 1;

    if (!ppLogicalDevice->CreateDescriptorPool(&tPoolInfo, nullptr, &poDescriptorPool))
    {
        throw std::runtime_error("failed to create descriptor pool!");
    }
}

void cMRTUniformHandler::CreateDescriptorSets(cTextureHandler* pTextureHandler, cScene* pScene)
{
    if (paoObjectUniformBuffers.size() > 0)
    {
        std::vector<VkDescriptorSetLayout> aoLayouts(paoObjectUniformBuffers.size(), poObjectDescriptorSetLayout);

        VkDescriptorSetAllocateInfo tAllocInfo = {};
        tAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;

        tAllocInfo.descriptorPool = poDescriptorPool;
        tAllocInfo.descriptorSetCount = (uint) paoObjectUniformBuffers.size();
        tAllocInfo.pSetLayouts = aoLayouts.data();

        poObjectDescriptorSets.resize((uint) paoObjectUniformBuffers.size());
        if (!ppLogicalDevice->AllocateDescriptorSets(&tAllocInfo, poObjectDescriptorSets.data()))
        {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }
    }

    uint uiIndex = 0;
    for (auto oObject : pScene->GetObjects())
    {
        VkDescriptorBufferInfo tBufferInfo = {};
        tBufferInfo.buffer = paoObjectUniformBuffers[uiIndex];
        tBufferInfo.offset = 0;
        tBufferInfo.range = sizeof(tObjectUniformData);

        cTexture* pTexture = oObject.second->GetMesh()->GetTexture();
        VkDescriptorImageInfo tImageInfo = {};
        tImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        tImageInfo.imageView = pTexture->GetView();
        tImageInfo.sampler = pTexture->GetSampler();

        cTexture* pMaterial = oObject.second->GetMesh()->GetMaterial();
        VkDescriptorImageInfo tMaterialInfo = {};
        tMaterialInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        tMaterialInfo.imageView = pMaterial->GetView();
        tMaterialInfo.sampler = pMaterial->GetSampler();

        std::array<VkWriteDescriptorSet, 3> atDescriptorWrites = {};

        atDescriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        atDescriptorWrites[0].dstSet = poObjectDescriptorSets[uiIndex];
        atDescriptorWrites[0].dstBinding = 0;
        atDescriptorWrites[0].dstArrayElement = 0;
        atDescriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        atDescriptorWrites[0].descriptorCount = 1;
        atDescriptorWrites[0].pBufferInfo = &tBufferInfo;

        atDescriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        atDescriptorWrites[1].dstSet = poObjectDescriptorSets[uiIndex];
        atDescriptorWrites[1].dstBinding = 1;
        atDescriptorWrites[1].dstArrayElement = 0;
        atDescriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        atDescriptorWrites[1].descriptorCount = 1;
        atDescriptorWrites[1].pImageInfo = &tImageInfo;

        atDescriptorWrites[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        atDescriptorWrites[2].dstSet = poObjectDescriptorSets[uiIndex];
        atDescriptorWrites[2].dstBinding = 2;
        atDescriptorWrites[2].dstArrayElement = 0;
        atDescriptorWrites[2].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        atDescriptorWrites[2].descriptorCount = 1;
        atDescriptorWrites[2].pImageInfo = &tMaterialInfo;

        ppLogicalDevice->UpdateDescriptorSets((uint) atDescriptorWrites.size(), atDescriptorWrites.data(),
                                              0, nullptr);

        oObject.second->GetMesh()->Validate();

        uiIndex++;
    }

    VkDescriptorSetAllocateInfo tCameraAllocateInfo = {};
    tCameraAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;

    tCameraAllocateInfo.descriptorPool = poDescriptorPool;
    tCameraAllocateInfo.descriptorSetCount = 1;
    tCameraAllocateInfo.pSetLayouts = &poCameraDescriptorSetLayout;

    if (!ppLogicalDevice->AllocateDescriptorSets(&tCameraAllocateInfo, &poCameraDescriptorSet))
    {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }

    VkDescriptorBufferInfo tCameraBufferInfo = {};
    tCameraBufferInfo.buffer = poCameraUniformBuffer;
    tCameraBufferInfo.offset = 0;
    tCameraBufferInfo.range = sizeof(tCameraUniformData);

    VkWriteDescriptorSet tCameraDescriptorWrite = {};
    tCameraDescriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    tCameraDescriptorWrite.dstSet = poCameraDescriptorSet;
    tCameraDescriptorWrite.dstBinding = 0;
    tCameraDescriptorWrite.dstArrayElement = 0;
    tCameraDescriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    tCameraDescriptorWrite.descriptorCount = 1;
    tCameraDescriptorWrite.pBufferInfo = &tCameraBufferInfo;

    ppLogicalDevice->UpdateDescriptorSets(1, &tCameraDescriptorWrite,
                                          0, nullptr);
}

void cMRTUniformHandler::UpdateDescriptorTexture(uint uiIndex, cTexture* pTexture)
{
    assert(pTexture != nullptr);

    VkDescriptorImageInfo tImageInfo = {};
    tImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    tImageInfo.imageView = pTexture->GetView();
    tImageInfo.sampler = pTexture->GetSampler();

    VkWriteDescriptorSet tDescriptorWrite = {};
    tDescriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    tDescriptorWrite.dstSet = poObjectDescriptorSets[uiIndex];
    tDescriptorWrite.dstBinding = 1;
    tDescriptorWrite.dstArrayElement = 0;
    tDescriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    tDescriptorWrite.descriptorCount = 1;
    tDescriptorWrite.pImageInfo = &tImageInfo;

    ppLogicalDevice->UpdateDescriptorSets(1, &tDescriptorWrite,
                                          0, nullptr);
}

uint cMRTUniformHandler::GetDescriptorSetLayoutCount()
{
    return 2;
}

VkDescriptorSetLayout* cMRTUniformHandler::GetDescriptorSetLayouts()
{
    return paoDescriptorSetLayouts;
}

void cMRTUniformHandler::CmdBindDescriptorSets(VkCommandBuffer& commandBuffer,
                                               VkPipelineLayout& oPipelineLayout,
                                               uint uiIndex)
{
    paoCurrentDescriptorSets[0] = poObjectDescriptorSets[uiIndex];
    paoCurrentDescriptorSets[1] = poCameraDescriptorSet;
    vkCmdBindDescriptorSets(commandBuffer,
                            VK_PIPELINE_BIND_POINT_GRAPHICS,
                            oPipelineLayout, 0,
                            2, paoCurrentDescriptorSets,
                            0, nullptr);
}

void cMRTUniformHandler::RebuildUniforms()
{
    Cleanup();
}

void cMRTUniformHandler::Cleanup()
{
    for (size_t i = 0; i < paoObjectUniformBuffers.size(); i++)
    {
        ppLogicalDevice->DestroyBuffer(paoObjectUniformBuffers[i], nullptr);
        ppLogicalDevice->FreeMemory(paoObjectUniformBuffersMemory[i], nullptr);
    }
    ppLogicalDevice->DestroyBuffer(poCameraUniformBuffer, nullptr);
    ppLogicalDevice->FreeMemory(poCameraUniformBufferMemory, nullptr);

    ppLogicalDevice->DestroyDescriptorPool(poDescriptorPool, nullptr);
}
