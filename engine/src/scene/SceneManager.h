#pragma once

#include <pch.h>
#include <scene/Scene.h>

class cSceneManager
{
private:
    cScene* ppActiveScene = nullptr;
    std::map<string, cScene*> pmpScenes;

    cLogicalDevice* ppLogicalDevice = nullptr;
    cTextureHandler* ppTextureHandler = nullptr;
    cGeometryHandler* ppGeometryHandler = nullptr;
//    cAudioHandler* ppAudioHandler = nullptr;

public:
    cSceneManager(cLogicalDevice* ppLogicalDevice,
                  cTextureHandler* ppTextureHandler,
                  cGeometryHandler* pGeometryHandler/*,
                  cAudioHandler* ppAudioHandler*/);
    void SwitchScene(const string& sName);

    std::map<string, cScene*>& GetScenes();
    cScene* GetActiveScene();
    virtual ~cSceneManager();
};
