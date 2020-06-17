#include <pch.hpp>
#include <Engine.hpp>
#include <TestScene.hpp>

class cApplication : public cEngine
{
public:
    cApplication() : cEngine("Test Game")
    {
        InitialiseMissions();
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

    void SetupScenes(std::map<string, cScene*>& mScenes, string* sInitialScene) override
    {
        mScenes["TestScene"] = new cTestScene();

        *sInitialScene = "TestScene";
    }

    void LoadOverlayWindows(std::map<string, cOverlayWindow*>& mOverlayWindows) override
    {

    }

    void InitialiseMissions()
    {

    }
};

int main(int argc, char** argv)
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