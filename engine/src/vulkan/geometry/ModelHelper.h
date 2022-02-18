#pragma once

#include <pch.h>
#include <vulkan/geometry/Vertex.h>

// Helper class for loading model files
class cModelHelper
{
public:
    // Load the vertices from a model file and optimize it into vertices and indices
    static void LoadModel(const char* sFilePath, std::vector<Vertex>& atVertices, std::vector<uint>& auiIndices);
};;
