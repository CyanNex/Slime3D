#include <scene/SceneManager.h>

cSceneManager::cSceneManager(cLogicalDevice* pLogicalDevice,
                             cTextureHandler* pTextureHandler,
                             cGeometryHandler* pGeometryHandler/*,
                             cAudioHandler* pAudioHandler*/)
{
    assert(pLogicalDevice != nullptr);
    assert(pTextureHandler != nullptr);
    assert(pGeometryHandler != nullptr);
//    assert(pAudioHandler != nullptr);

    ppLogicalDevice = pLogicalDevice;
    ppTextureHandler = pTextureHandler;
    ppGeometryHandler = pGeometryHandler;
//    ppAudioHandler = pAudioHandler;
}

cSceneManager::~cSceneManager()
{
    for (auto&[sName, pScene] : pmpScenes)
    {
        delete pScene;
    }
}

void cSceneManager::SwitchScene(const string& sName)
{
    auto tResult = pmpScenes.find(sName);
    assert(tResult != pmpScenes.end()); // scene must exist

    if (ppActiveScene != nullptr)
    {
        ENGINE_LOG("Unloading active scene...");
        ppActiveScene->Unload();
    }

    ENGINE_LOG("Loading new scene...");
    ppActiveScene = tResult->second;
    ppActiveScene->Load(ppTextureHandler, ppGeometryHandler, ppLogicalDevice/*, ppAudioHandler*/);
}

std::map<string, cScene*>& cSceneManager::GetScenes()
{
    return pmpScenes;
}

cScene* cSceneManager::GetActiveScene()
{
    return ppActiveScene;
}
