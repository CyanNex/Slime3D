#pragma once

#include <pch.h>

#include <GameManager.h>
#include <loop/GameLoop.h>
#include <scene/Scene.h>
#include <scene/SceneManager.h>
#include <audio/AudioHandler.h>

#include <vulkan/Window.h>
#include <vulkan/VulkanInstance.h>
#include <vulkan/LogicalDevice.h>
#include <vulkan/RenderHandler.h>
#include <vulkan/swapchain/SwapChain.h>
#include <vulkan/command/CommandBuffer.h>
#include <vulkan/command/CommandBufferHolder.h>
#include <vulkan/uniform/UniformHandler.h>

#include <vulkan/texture/TextureHandler.h>
#include <vulkan/geometry/GeometryHandler.h>

#include <vulkan/module/mrt/MRTRenderModule.h>
#include <vulkan/module/lighting/LightingRenderModule.h>
#include <vulkan/module/overlay/OverlayRenderModule.h>
#include <vulkan/module/scene/SceneRenderModule.h>

class cEngine : public iGameManager, public iInputHandler, public iCommandBufferHolder
{
private:
    const string psAppName;

    // Application window instance
    cWindow* ppWindow = nullptr;
    // Vulkan API instance
    cVulkanInstance* ppVulkanInstance = nullptr;

    // Logical representation of the graphical device
    cLogicalDevice* ppLogicalDevice = nullptr;
    // Swap chain for managing frame buffers
    cSwapChain* ppSwapChain = nullptr;
    // Texture handler for loading and managing textures
    cTextureHandler* ppTextureHandler = nullptr;
    cGeometryHandler* ppGeometryHandler = nullptr;

    // Render handler for handling frame drawing logic
    cRenderHandler* ppRenderHandler = nullptr;

    // Render modules for MRT (multi render target, overlay, and lighting
    // Render modules manage the uniforms, graphics pipeline, and render pass
    cMRTRenderModule* ppMRTRenderModule = nullptr;
    cOverlayRenderModule* ppOverlayRenderModule = nullptr;
    cLightingRenderModule* ppLightsRenderModule = nullptr;
    cSceneRenderModule* ppSceneRenderModule = nullptr;

    // Command buffers for all render modules
    cCommandBuffer* papCommandBuffers[4] = {};
    // Uniform handlers for all render modules
    iUniformHandler* papUniformHandlers[4] = {};

    // Gameloop and thread for the gameloop
    cGameLoop* ppGameLoop = nullptr;
    std::thread* ppGameThread = nullptr;

    // Scene manager for storing and loading scenes
    cSceneManager* ppSceneManager = nullptr;
    // Audio handler for playing audio
    cAudioHandler* ppAudioHandler = nullptr;

    // Map with all loaded overlay windows
//    std::map<string, cOverlayWindow*> pmOverlayWindows;
    // Current active overlay window
//    cOverlayWindow* ppActiveOverlayWindow = nullptr;

    // Variables for requesting an overlay window change
//    cOverlayWindow* ppRequestedOverlayWindow = nullptr;
//    bool pbUpdateOverlayWindow = false;

    // Variables for requesting a scene change
    string psRequestedScene;
    bool pbUpdateScene = false;

    // Property indicating if the engine is fully initialized
    bool pbInitialized = false;

public:
    cEngine(string sAppName = "Game");

    // Initializes and starts the engine and all of it's subcomponents
    void Run();

    // Get the currently active overlay window
    // Can be null if no window is active
//    cOverlayWindow* GetActiveOverlayWindow() override;
    // Request a certain overlay window to be activated
//    void ActivateOverlayWindow(const string& sName) override;
    // Activates by pointer.
//    void ActivateOverlayWindow(cOverlayWindow* pWindow) override;
    // Returns overlay by name
//    cOverlayWindow* GetOverlayByName(const string& sName) override;
    // Request the active overlay window to be deactivated
//    void DeactivateOverlayWindow() override;
    // Request a scene switch
    void SwitchScene(const string& sName) override;
    // Get all the scenes
    std::map<string, cScene*>& GetScenes() override;

    // Get an array with the command buffers
    // TODO: Remove this method
    cCommandBuffer** GetCommandBuffers() override;

    // Input handling
    void HandleMouse(double dDeltaX, double dDeltaY) override;
    void HandleKey(uint uiKeyCode, uint uiAction) override;
    void HandleScroll(double dOffsetX, double dOffsetY) override;
    void HandleCharacter(char cCharacter) override;
    void HandleMouseButton(uint uiButton, double dXPos, double dYPos, int iAction) override;

protected:
    // Shader loading from the application
    virtual void LoadMRTShaders(std::vector<string>& shaders) = 0;
    virtual void LoadLightingShaders(std::vector<string>& shaders) = 0;
    virtual void LoadOverlayShaders(std::vector<string>& shaders) = 0;
    virtual void LoadSceneShaders(std::vector<string>& shaders) = 0;

    // Overlay and scene loading from the application
//    virtual void LoadOverlayWindows(std::map<string, cOverlayWindow*>& mOverlayWindows) = 0;
    virtual void SetupScenes(std::map<string, cScene*>& mScenes, string* sInitialScene) = 0;

private:
    // Initialization
    void InitWindow();
    void InitAudio();
    void InitVulkan();
    void InitEngine();
    // Engine main loop
    void MainLoop();
    // Engine cleanup
    void Cleanup();

    // Switch the active overlay window
    void UpdateOverlay();
    // Switch the active scene
    void UpdateScene();

    // Rebuild the entire pipeline
    void RebuildPipeline();
    // (Re-)record the command buffers
    void RecordCommandBuffers();
    // Rebuild the uniforms
    void RebuildUniforms();
};
