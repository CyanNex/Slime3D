#pragma once

#include <pch.h>
#include <GLFW/glfw3.h>
#include <vulkan/VulkanInstance.h>
#include <scene/InputHandler.h>

// Class representing the window which can be used for rendering
class cWindow
{
public:
    static uint puiWidth;
    static uint puiHeight;
    static uint puiRefreshRate;

private:
    static cWindow* poInstance;

    const string& psWindowName;

    cVulkanInstance* ppVulkanInstance = nullptr;
    VkSurfaceKHR poSurface = VK_NULL_HANDLE;

    uint puiWindowWidth = 0;
    uint puiWindowHeight = 0;
    int puiWindowX = 0;
    int puiWindowY = 0;

    bool pbRequestRebuild = false;
    bool pbFullscreen = false;

public:
    // Pointer to the GLFW window instance
    GLFWwindow* ppWindow = nullptr;

    iInputHandler* ppInputHandler = nullptr;

    explicit cWindow(const string& sWindowName = "");
    ~cWindow();

    // Create and initialize the window
    void CreateGLWindow();

    // Create the surface for this window
    bool CreateWindowSurface(cVulkanInstance* pVulkanInstance);

    // Destroy the surface for this window
    // Must be called before destroying the vulkan instance
    void DestroyWindowSurface();

    // Returns true if the window should close
    [[nodiscard]] bool ShouldClose() const;

    [[nodiscard]] bool ShouldRebuild() const;

    // Handles window events
    void HandleEvents();

    // Mark this window as should close
    void Close() const;

    VkSurfaceKHR& GetSurface();

    static void SetResolution(uint uiWidth, uint uiHeight);
    static void SetFullscreen(bool bFullscreen);
    static void SetMouseLocked(bool bLocked);
    static void RequestRebuild();
    static void HandleMinimize();
    void RebuildSurface();

private:
    void FindAndHandleGamepad() const;
    void HandleGamepad(uint uiJoystickId) const;

    static void mouseCallback(GLFWwindow* pWindow, double dPosX, double dPosY);
    static void keyCallback(GLFWwindow* pWindow, int iKey, int iScanCode, int iAction, int iMods);
    static void scrollCallback(GLFWwindow* pWindow, double dOffsetX, double dOffsetY);
    static void characterCallback(GLFWwindow* pWindow, uint uiCharacter);
    static void mouseButtonCallback(GLFWwindow* pWindow, int iButton, int iAction, int iMods);
};

