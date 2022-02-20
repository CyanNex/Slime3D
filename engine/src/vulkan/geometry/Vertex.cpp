#include <vulkan/geometry/Vertex.h>

VkVertexInputBindingDescription Vertex::GetBindingDescription()
{
    // Struct specifying vertex input binding
    VkVertexInputBindingDescription tBindingDescription = {};
    tBindingDescription.binding = 0;                                // binding number for vertices
    tBindingDescription.stride = sizeof(Vertex);                    // distance between two elements
    tBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;    // defines vertex addressing function

    return tBindingDescription;
}

std::vector<VkVertexInputAttributeDescription> Vertex::GetAttributeDescriptions()
{
    std::vector<VkVertexInputAttributeDescription> atAttributeDescriptions(4);

    // Attribute at location 0 (pos)
    atAttributeDescriptions[0].binding = 0;
    atAttributeDescriptions[0].location = 0;
    atAttributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    atAttributeDescriptions[0].offset = offsetof(Vertex, pos);

    // Attribute at location 1 (normal)
    atAttributeDescriptions[1].binding = 0;
    atAttributeDescriptions[1].location = 1;
    atAttributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    atAttributeDescriptions[1].offset = offsetof(Vertex, normal);

    // Attribute at location 2 (color)
    atAttributeDescriptions[2].binding = 0;
    atAttributeDescriptions[2].location = 2;
    atAttributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
    atAttributeDescriptions[2].offset = offsetof(Vertex, color);

    // Attribute at location 3 (texCoord)
    atAttributeDescriptions[3].binding = 0;
    atAttributeDescriptions[3].location = 3;
    atAttributeDescriptions[3].format = VK_FORMAT_R32G32_SFLOAT;
    atAttributeDescriptions[3].offset = offsetof(Vertex, texCoord);

    return atAttributeDescriptions;
}

bool Vertex::operator==(const Vertex& other) const
{
    return pos == other.pos && color == other.color && texCoord == other.texCoord && normal == other.normal;
}
