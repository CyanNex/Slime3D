#include <pch.h>
#include <Engine.h>
#include <TestScene.h>

class cApplication : public cEngine
{
public:
    cApplication() : cEngine("Test Game")
    {
    }

protected:
    void LoadMRTShaders(std::vector<string>& shaders) override
    {
        shaders.emplace_back("resources/shaders/compiled/mrt.vert.spv");
        shaders.emplace_back("resources/shaders/compiled/mrt.frag.spv");
    }

    void LoadLightingShaders(std::vector<string>& shaders) override
    {
        shaders.emplace_back("resources/shaders/compiled/lighting.vert.spv");
        shaders.emplace_back("resources/shaders/compiled/lighting.frag.spv");
    }

    void LoadOverlayShaders(std::vector<string>& shaders) override
    {
        shaders.emplace_back("resources/shaders/compiled/text.vert.spv");
        shaders.emplace_back("resources/shaders/compiled/text.frag.spv");
    }

    void LoadSceneShaders(std::vector<string>& shaders) override
    {
        shaders.emplace_back("resources/shaders/compiled/scene.vert.spv");
        shaders.emplace_back("resources/shaders/compiled/scene.frag.spv");
    }

    void SetupScenes(std::map<string, cScene*>& mScenes, string* sInitialScene) override
    {
        mScenes["TestScene"] = new cTestScene();

        *sInitialScene = "TestScene";
    }
};

int main()
{
    cApplication oGame;

    try
    {
        oGame.Run();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
