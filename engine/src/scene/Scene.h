#pragma once

#include <pch.h>
#include <loop/TickTask.h>
#include <vulkan/mesh/Mesh.h>
#include <vulkan/geometry/Geometry.h>
#include <scene/object/BaseObject.h>
#include <scene/object/LightObject.h>
#include <scene/camera/Camera.h>
#include <scene/camera/FirstPersonFlyCamera.h>
#include <vulkan/texture/TextureHandler.h>
#include <scene/InputHandler.h>
#include <vulkan/geometry/ViewportQuadGeometry.h>
#include <vulkan/geometry/GeometryHandler.h>
#include <util/Profiler.h>

class cScene : public iInputHandler, public iTickTask
{
private:
    bool bQuit = false;

protected:
    cCamera* poCamera = new cFirstPersonFlyCamera;

    std::map<string, cTexture*> pmpTextures;
    std::map<string, cGeometry*> pmpGeometries;
    std::map<string, cMesh*> pmpMeshes;

    std::map<string, cBaseObject*> pmpObjects;

    bool paKeys[GLFW_KEY_LAST] = {false};

    cColliderSet* ppColliders = new cColliderSet();

private:
    std::vector<cBaseObject*> papMovableObjects;
    std::vector<cLightObject*> papLightObjects;

public:
    float pfAmbientLight = 0.3f;

    cScene();
    virtual ~cScene();

    void Tick() override;
    virtual void Update();

    uint GetObjectCount();
    std::map<string, cBaseObject*>& GetObjects();
    std::vector<cBaseObject*>& GetMovableObjects();
    std::vector<cLightObject*>& GetLightObjects();

    cCamera& GetCamera();
    cCamera** GetCameraRef();

    bool ShouldQuit();

    virtual void Load(cTextureHandler* pTextureHandler,
                      cGeometryHandler* pGeometryHandler,
                      cLogicalDevice* pLogicalDevice);
    virtual void Unload();
    void UnloadObjects();

    void HandleMouse(double dDeltaX, double dDeltaY) override;
    void HandleKey(uint uiKeyCode, uint uiAction) override;
    void HandleScroll(double dOffsetX, double dOffsetY) override;
    void HandleCharacter(char cCharacter) override;

    virtual void OnInputDisable();
    void HandleMouseButton(uint uiButton, double dXPos, double dYPos, int iAction) override;

    virtual void AfterLoad();
protected:
    void Quit();
};
