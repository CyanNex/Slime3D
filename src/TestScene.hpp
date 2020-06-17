#pragma once

#include <vulkan/scene/Scene.hpp>

class cTestScene : public cScene
{
public:
    void Load(cTextureHandler* pTextureHandler,
              cGeometryHandler* pGeometryHandler,
              cLogicalDevice* pLogicalDevice,
              cAudioHandler* pAudioHandler) override;
    void Update() override;
};

void cTestScene::Load(cTextureHandler* pTextureHandler,
                      cGeometryHandler* pGeometryHandler,
                      cLogicalDevice* pLogicalDevice,
                      cAudioHandler* pAudioHandler)
{
    pmpTextures["test_texture"] = pTextureHandler->LoadFromFile("resources/textures/test_texture.png");

    pmpGeometries["test_geometry"] = pGeometryHandler->LoadFromFile("resources/geometries/test_geometry.obj");

    pmpMeshes["test_mesh"] = new cMesh(pmpGeometries["test_geometry"], pmpTextures["test_texture"]);

    pmpObjects["test_object"] = new cBaseObject(pmpMeshes["test_mesh"]);

    pmpObjects["test_light"] = new cLightObject(pmpMeshes["test_mesh"], glm::vec3(1, 0, 1), 12);
    pmpObjects["test_light"]->SetPosition(glm::vec3(2, 2, 2));
    pmpObjects["test_light"]->SetScale(glm::vec3(0.05, 0.05, 0.05));

    glm::vec3 tCameraPos(3, 2, 4);
    poCamera->SetPosition(tCameraPos);

    cScene::Load(pTextureHandler, pGeometryHandler, pLogicalDevice, pAudioHandler);
}

void cTestScene::Update()
{
    if (paKeys[GLFW_KEY_W])
        poCamera->Forward();
    if (paKeys[GLFW_KEY_S])
        poCamera->BackWard();
    if (paKeys[GLFW_KEY_A])
        poCamera->MoveLeft();
    if (paKeys[GLFW_KEY_D])
        poCamera->MoveRight();
    if (paKeys[GLFW_KEY_SPACE])
        poCamera->MoveUp();
    if (paKeys[GLFW_KEY_LEFT_SHIFT])
        poCamera->MoveDown();

    cScene::Update();
}
