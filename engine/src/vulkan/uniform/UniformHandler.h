#pragma once

#include <pch.h>
#include <vulkan/texture/TextureHandler.h>
#include <scene/Scene.h>

class iUniformHandler
{
public:
    virtual ~iUniformHandler() = default;

    virtual void SetupUniformBuffers(cTextureHandler* pTextureHandler, cScene* pScene) = 0;
    virtual void UpdateUniformBuffers(cScene* pScene) = 0;

    virtual uint GetDescriptorSetLayoutCount() = 0;
    virtual VkDescriptorSetLayout* GetDescriptorSetLayouts() = 0;

    virtual void RebuildUniforms() = 0;

    virtual void CmdBindDescriptorSets(VkCommandBuffer& commandBuffer,
                                       VkPipelineLayout& oPipelineLayout,
                                       uint uiIndex) = 0;
};
