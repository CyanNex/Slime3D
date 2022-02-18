#pragma once

#include <pch.h>
#include <vulkan/LogicalDevice.h>

class cPipelineHelper
{
public:
    static VkShaderModule CreateShaderModule(const std::vector<char>& asCode, cLogicalDevice* pLogicalDevice);
    static std::vector<char> ReadFile(const std::string& sFilename);

    static VkPipelineRasterizationStateCreateInfo GetRasterizerCreateInfo(VkFrontFace eFrontFace);
    static VkPipelineDepthStencilStateCreateInfo GetDepthStencilCreateInfo();
};
