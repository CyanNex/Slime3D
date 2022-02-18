#pragma once

#include <pch.h>
#include <vulkan/vulkan_core.h>

struct tVertex2D
{
    glm::vec2 pos;
    glm::vec2 texCoord;

    static std::array<VkVertexInputBindingDescription, 1> GetBindingDescriptions();
    static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions();
};

