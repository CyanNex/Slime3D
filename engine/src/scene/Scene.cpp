#include <scene/Scene.h>
#include <util/UtilFunctions.h>

cScene::cScene() = default;

cScene::~cScene()
{
    delete ppColliders;
    delete poCamera;

    UnloadObjects();

    ENGINE_LOG("Cleaned up scene");
}

void cScene::Load(cTextureHandler* pTextureHandler,
                  cGeometryHandler* pGeometryHandler,
                  cLogicalDevice* pLogicalDevice)
{
    for (const auto& oTexture : pmpTextures)
    {
        assert(oTexture.second != nullptr);
    }

    for (const auto& oGeometry : pmpGeometries)
    {
        assert(oGeometry.second != nullptr);
    }

    for (auto oMesh : pmpMeshes)
    {
        assert(oMesh.second != nullptr);
        oMesh.second->Validate();
    }

    for (auto oObject : pmpObjects)
    {
        assert(oObject.second != nullptr);

        // If the object isn't static, add it to the list of movable objects
        if (!oObject.second->IsStatic())
        {
            papMovableObjects.push_back(oObject.second);
        }

        // If the object is a light source, add it to the list of light sources
        if (instanceOf<cLightObject>(oObject.second))
        {
            papLightObjects.push_back(dynamic_cast<cLightObject*>(oObject.second));
        }

        // If the object is a collider, set it up and add it to the collider set
        cCollider* pCollider = oObject.second->GetCollider();
        if (pCollider != nullptr)
        {
            pCollider->Update(oObject.second->GetModelMatrix());
            ppColliders->papColliders.push_back(pCollider);
        }

        oObject.second->Setup(ppColliders);
    }

    pTextureHandler->WaitForLoadComplete();
    pGeometryHandler->WaitForLoadComplete();

    ENGINE_LOG("Loaded "
                       << pmpTextures.size() << " textures, "
                       << pmpGeometries.size() << " geometries, "
                       << pmpMeshes.size() << " meshes, and "
                       << pmpObjects.size() << " objects, of which " << papMovableObjects.size()
                       << " are movable and " << papLightObjects.size() << " are lights");
}

void cScene::Unload()
{
    UnloadObjects();

    papLightObjects.clear();
    papMovableObjects.clear();
    ppColliders->papColliders.clear();
    poCamera->Reset();
}

void cScene::UnloadObjects()
{
    for (const auto& oObject : pmpObjects)
    {
        delete oObject.second;
    }
    pmpObjects.clear();

    for (const auto& oMesh : pmpMeshes)
    {
        delete oMesh.second;
    }
    pmpMeshes.clear();

    pmpGeometries.clear();
    pmpTextures.clear();
}

void cScene::Tick()
{
    Update();
}

void cScene::Update()
{
    poCamera->ProcessUpdates();
}

uint cScene::GetObjectCount()
{
    return (uint) pmpObjects.size();
}

std::map<string, cBaseObject*>& cScene::GetObjects()
{
    return pmpObjects;
}

std::vector<cBaseObject*>& cScene::GetMovableObjects()
{
    return papMovableObjects;
}

std::vector<cLightObject*>& cScene::GetLightObjects()
{
    return papLightObjects;
}

cCamera& cScene::GetCamera()
{
    return *poCamera;
}

void cScene::Quit()
{
    bQuit = true;
}

bool cScene::ShouldQuit()
{
    return bQuit;
}

void cScene::HandleMouse(double dDeltaX, double dDeltaY)
{
    poCamera->LookMouseDiff(dDeltaX, dDeltaY);
}

void cScene::HandleKey(uint uiKeyCode, uint uiAction)
{
    if (uiKeyCode != 0 && uiKeyCode < GLFW_KEY_LAST)
    {
        if (uiAction == GLFW_PRESS) paKeys[uiKeyCode] = true;
        if (uiAction == GLFW_RELEASE) paKeys[uiKeyCode] = false;
    }
}

void cScene::HandleScroll(double dOffsetX, double dOffsetY)
{

}

void cScene::HandleCharacter(char cCharacter)
{

}

void cScene::HandleMouseButton(uint uiButton, double dXPos, double dYPos, int iAction)
{

}

cCamera** cScene::GetCameraRef()
{
    return &poCamera;
}

void cScene::OnInputDisable()
{
    for (bool& paKey : paKeys)
    {
        paKey = false;
    }
}

void cScene::AfterLoad()
{
}
