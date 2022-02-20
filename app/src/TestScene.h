#pragma once

#include <scene/Scene.h>
#include <audio/AudioSource.h>

class cTestScene : public cScene
{
public:
    void Load(cTextureHandler* pTextureHandler,
              cGeometryHandler* pGeometryHandler,
              cLogicalDevice* pLogicalDevice) override;
    void Update() override;

private:
    cAudioSource* ppSourceObject;
};
