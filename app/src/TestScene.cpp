#include <TestScene.h>

void cTestScene::Load(cTextureHandler* pTextureHandler,
                      cGeometryHandler* pGeometryHandler,
                      cLogicalDevice* pLogicalDevice)
{
    pmpTextures["test_texture"] = pTextureHandler->LoadFromFile("resources/textures/test_texture.png");

    pmpGeometries["test_geometry"] = pGeometryHandler->LoadFromFile("resources/geometries/test_geometry.obj");

    pmpMeshes["test_mesh"] = new cMesh(pmpGeometries["test_geometry"], pmpTextures["test_texture"]);

    cAudioSample* pSample = cAudioSample::FromFile("resources/test.wav");
    ppSourceObject = new cAudioSource(pmpMeshes["test_mesh"], nullptr, false);
    ppSourceObject->Load(pSample, false);
    pmpObjects["test_object"] = ppSourceObject;

    pmpObjects["test_light"] = new cLightObject(pmpMeshes["test_mesh"], glm::vec3(1, 0, 1), 12);
    pmpObjects["test_light"]->SetPosition(glm::vec3(2, 2, 2));
    pmpObjects["test_light"]->SetScale(glm::vec3(0.05, 0.05, 0.05));

    glm::vec3 tCameraPos(-3, 2, -4);
    poCamera->SetPosition(tCameraPos);

    cScene::Load(pTextureHandler, pGeometryHandler, pLogicalDevice);
}

void cTestScene::Update()
{
    static bool bStarted = false;

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
    if (paKeys[GLFW_KEY_ESCAPE])
        this->Quit();

    if (paKeys[GLFW_KEY_E] && !bStarted)
    {
        bStarted = true;
        ppSourceObject->Play();
    }

    if (paKeys[GLFW_KEY_R] && bStarted)
    {
        bStarted = false;
        ppSourceObject->Stop();
    }

    cScene::Update();
}
