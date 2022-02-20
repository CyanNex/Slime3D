#pragma once

#define GLM_ENABLE_EXPERIMENTAL // We need GLM experimental features for our hash function

#include <pch.h>
#include <vulkan/vulkan.h>
#include <glm/gtx/hash.hpp>

// Struct describing a vertex
struct Vertex
{
    // Position of this vertex in 3D space
    glm::vec3 pos;

    // Normal of this vertex
    glm::vec3 normal;

    // Color of this vertex
    glm::vec3 color;

    // Texture coordinate to use for this vertex
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription GetBindingDescription();
    static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();

    bool operator==(const Vertex& other) const;
};

// Hash function for vertices
namespace std
{
    template<>
    struct hash<Vertex>
    {
        size_t operator()(Vertex const& vertex) const
        {
            return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
                   ((hash<glm::vec2>()(vertex.texCoord) ^ (hash<glm::vec3>()(vertex.normal) << 1)) >> 1);
        }
    };
}
