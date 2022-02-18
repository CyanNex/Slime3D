#pragma once

#include <pch.h>
#include <scene/Scene.h>

class iGameManager
{
public:
//    virtual cOverlayWindow* GetActiveOverlayWindow() = 0;
//    virtual void ActivateOverlayWindow(const string& sName) = 0;
//    virtual void ActivateOverlayWindow(cOverlayWindow* pWindow) = 0;
//    virtual cOverlayWindow* GetOverlayByName(const string& sName) = 0;
//    virtual void DeactivateOverlayWindow() = 0;
    virtual void SwitchScene(const string& sName) = 0;
    virtual std::map<string, cScene*>& GetScenes() = 0;
};
