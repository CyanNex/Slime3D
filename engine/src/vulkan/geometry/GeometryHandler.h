#pragma once

#include <pch.h>
#include <vulkan/LogicalDevice.h>
#include <vulkan/geometry/Geometry.h>
#include <util/AsyncLoader.hpp>

class cGeometryHandler : public cAsyncLoader<cGeometry>
{
private:
    cLogicalDevice* ppLogicalDevice;

    std::map<string, cGeometry*> pmpGeometries;

public:
    cGeometryHandler(cLogicalDevice* pLogicalDevice);
    ~cGeometryHandler();

    cGeometry* LoadFromFile(const string& sFilePath, const glm::vec2& tUVScale);
    cGeometry* LoadFromFile(const string& sFilePath);

protected:
    void LoadCallback(cGeometry* pObject) override;
};;
