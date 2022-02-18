#pragma once

#include <scene/Scene.h>

class cTestScene : public cScene
{
public:
    void Load(cTextureHandler* pTextureHandler,
              cGeometryHandler* pGeometryHandler,
              cLogicalDevice* pLogicalDevice) override;
    void Update() override;
};
