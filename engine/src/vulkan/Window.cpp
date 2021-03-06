#include <vulkan/Window.h>
#include <util/UtilFunctions.h>

cWindow* cWindow::poInstance = nullptr;

uint cWindow::puiWidth = 1920;
uint cWindow::puiHeight = 1080;
uint cWindow::puiRefreshRate = 60;

cWindow::cWindow(const string& sWindowName) : psWindowName(sWindowName)
{
    glfwInit();

    // We don't want to create an OpenGL context, so specify NO_API
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // Window resizing is temporarily disabled
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    poInstance = this;
}

cWindow::~cWindow()
{

    // Destroy the GLFW window if it exists
    if (ppWindow != nullptr)
    {
        glfwDestroyWindow(ppWindow);
    }

    // Terminate GLFW
    glfwTerminate();
}

void cWindow::CreateGLWindow()
{
    assert(ppWindow == nullptr); // don't create a window if it has already been created

    ppWindow = glfwCreateWindow(cWindow::puiWidth, cWindow::puiHeight,
                                psWindowName.c_str(), nullptr, nullptr);

    glfwSetCursorPosCallback(ppWindow, mouseCallback);
    glfwSetKeyCallback(ppWindow, keyCallback);
    glfwSetScrollCallback(ppWindow, scrollCallback);
    glfwSetCharCallback(ppWindow, characterCallback);
    glfwSetMouseButtonCallback(ppWindow, mouseButtonCallback);

    glfwGetWindowPos(poInstance->ppWindow, &poInstance->puiWindowX, &poInstance->puiWindowY);
}

bool cWindow::CreateWindowSurface(cVulkanInstance* pVulkanInstance)
{
    assert(pVulkanInstance != nullptr); // vulkan instance should exist

    ppVulkanInstance = pVulkanInstance;

    return pVulkanInstance->CreateWindowSurface(ppWindow, nullptr, &poSurface);
}

void cWindow::DestroyWindowSurface()
{
    assert(ppVulkanInstance != nullptr); // vulkan instance must exist

    ppVulkanInstance->DestroyWindowSurface(poSurface, nullptr);
}

bool cWindow::ShouldClose() const
{
    assert(ppWindow != nullptr); // window must be created first

    return glfwWindowShouldClose(ppWindow);
}

bool cWindow::ShouldRebuild() const
{
    return pbRequestRebuild;
}

void cWindow::HandleEvents()
{
    assert(ppWindow != nullptr); // window must be created first

    if (ppInputHandler != nullptr)
    {
        glfwPollEvents();
        FindAndHandleGamepad();
    }
}

void cWindow::Close() const
{
    glfwSetWindowShouldClose(ppWindow, GLFW_TRUE);
}

VkSurfaceKHR& cWindow::GetSurface()
{
    assert(poSurface != VK_NULL_HANDLE);

    return poSurface;
}

void cWindow::FindAndHandleGamepad() const
{
    if (poInstance == nullptr || poInstance->ppInputHandler == nullptr) return;

    for (uint uiJoystickId = GLFW_JOYSTICK_1; uiJoystickId < GLFW_JOYSTICK_LAST; uiJoystickId++)
    {
        // Check if the joystick is a gamepad
        if (glfwJoystickIsGamepad(uiJoystickId))
        {
            HandleGamepad(uiJoystickId);
        }
    }
}

void cWindow::HandleGamepad(uint uiJoystickId) const
{
    if (poInstance == nullptr || poInstance->ppInputHandler == nullptr) return;

    GLFWgamepadstate tState;
    if (glfwGetGamepadState(uiJoystickId, &tState))
    {
        // Pass the right stick on as mouse input
        ppInputHandler->HandleMouse((uint) tState.axes[GLFW_GAMEPAD_AXIS_RIGHT_X],
                                    (uint) tState.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]);

        // Temporary mapping for the left stick to keyboard keys
        float fMoveY = tState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] - (tState.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] + 1);
        if (fMoveY < -0.1) ppInputHandler->HandleKey(GLFW_KEY_W, GLFW_PRESS);
        else if (fMoveY > 0.1) ppInputHandler->HandleKey(GLFW_KEY_S, GLFW_PRESS);
        else
        {
            ppInputHandler->HandleKey(GLFW_KEY_W, GLFW_RELEASE);
            ppInputHandler->HandleKey(GLFW_KEY_S, GLFW_RELEASE);
        }

        float fMoveX = tState.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
        if (fMoveX < -0.1) ppInputHandler->HandleKey(GLFW_KEY_A, GLFW_PRESS);
        else if (fMoveX > 0.1) ppInputHandler->HandleKey(GLFW_KEY_D, GLFW_PRESS);
        else
        {
            ppInputHandler->HandleKey(GLFW_KEY_A, GLFW_RELEASE);
            ppInputHandler->HandleKey(GLFW_KEY_D, GLFW_RELEASE);
        }

        // Temporary mapping for the back, start and menu buttons to the escape key
        if (tState.buttons[GLFW_GAMEPAD_BUTTON_BACK] ||
            tState.buttons[GLFW_GAMEPAD_BUTTON_START] ||
            tState.buttons[GLFW_GAMEPAD_BUTTON_GUIDE])
        {
            ppInputHandler->HandleKey(GLFW_KEY_ESCAPE, GLFW_PRESS);
        } else
        {
            ppInputHandler->HandleKey(GLFW_KEY_ESCAPE, GLFW_RELEASE);
        }
    }
}

void cWindow::mouseCallback(GLFWwindow* pWindow, double dPosX, double dPosY)
{
    static bool bFirstMouse = true;
    static double dLastX = puiWidth, dLastY = puiHeight;

    if (poInstance == nullptr || poInstance->ppInputHandler == nullptr) return;

    // If this is the first time the mouse is moved, set
    // the last position to the current
    if (bFirstMouse)
    {
        dLastX = dPosX;
        dLastY = dPosY;
        bFirstMouse = false;
    }

    // Calculate the delta between the last and current position
    double dDeltaX = dPosX - dLastX;
    double dDeltaY = dPosY - dLastY;

    // Set the last position to the current
    dLastX = dPosX;
    dLastY = dPosY;

    // Apply a sensitivity factor
    const float fSensitivity = 2.5f;
    dDeltaX *= fSensitivity;
    dDeltaY *= fSensitivity;

    // Pass the delta X and Y on to the input handler
    poInstance->ppInputHandler->HandleMouse(dDeltaX, dDeltaY);
}

void cWindow::keyCallback(GLFWwindow* pWindow, int iKey, int iScanCode, int iAction, int iMods)
{
    if (poInstance == nullptr || poInstance->ppInputHandler == nullptr) return;

    poInstance->ppInputHandler->HandleKey(iKey, iAction);
}

void cWindow::scrollCallback(GLFWwindow* pWindow, double dOffsetX, double dOffsetY)
{
    if (poInstance == nullptr || poInstance->ppInputHandler == nullptr) return;

    poInstance->ppInputHandler->HandleScroll(dOffsetX, dOffsetY);
}

void cWindow::characterCallback(GLFWwindow* pWindow, uint uiCharacter)
{
    if (poInstance == nullptr || poInstance->ppInputHandler == nullptr) return;

    poInstance->ppInputHandler->HandleCharacter((char) uiCharacter);
}

void cWindow::mouseButtonCallback(GLFWwindow* pWindow, int iButton, int iAction, int iMods)
{
    if (poInstance == nullptr || poInstance->ppInputHandler == nullptr) return;

    double dXPos, dYPos;
    glfwGetCursorPos(pWindow, &dXPos, &dYPos);

    poInstance->ppInputHandler->HandleMouseButton((uint) iButton, dXPos, dYPos, iAction);
}

void cWindow::SetResolution(uint uiWidth, uint uiHeight)
{
    glfwGetWindowPos(poInstance->ppWindow, &poInstance->puiWindowX, &poInstance->puiWindowY);

    puiWidth = uiWidth;
    puiHeight = uiHeight;
    poInstance->pbRequestRebuild = true;
}

void cWindow::SetFullscreen(bool bFullscreen)
{
    if (bFullscreen)
    {
        glfwGetWindowPos(poInstance->ppWindow, &poInstance->puiWindowX, &poInstance->puiWindowY);

        poInstance->puiWindowWidth = puiWidth;
        poInstance->puiWindowHeight = puiHeight;

        GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* pVideoMode = glfwGetVideoMode(pMonitor);
        puiWidth = pVideoMode->width;
        puiHeight = pVideoMode->height;
        puiRefreshRate = pVideoMode->refreshRate;
        poInstance->pbFullscreen = true;
        poInstance->pbRequestRebuild = true;
    } else
    {
        puiWidth = poInstance->puiWindowWidth;
        puiHeight = poInstance->puiWindowHeight;
        poInstance->pbFullscreen = false;
        poInstance->pbRequestRebuild = true;
    }
}

void cWindow::RequestRebuild()
{
    poInstance->pbRequestRebuild = true;
}

void cWindow::SetMouseLocked(bool bLocked)
{
#ifndef UNLOCK_CURSOR
    glfwSetInputMode(poInstance->ppWindow, GLFW_CURSOR, !bLocked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    sleep_ms(10);
    glfwSetInputMode(poInstance->ppWindow, GLFW_CURSOR, bLocked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
#endif
}

void cWindow::RebuildSurface()
{
    ENGINE_LOG(puiWidth << "x" << puiHeight << "@" << puiWindowX << "," << puiWindowY);
    DestroyWindowSurface();
    sleep_ms(200);
    if (pbFullscreen)
    {
        glfwSetWindowMonitor(ppWindow, glfwGetPrimaryMonitor(), 0, 0, puiWidth, puiHeight, puiRefreshRate);
    } else
    {
        glfwSetWindowMonitor(ppWindow, nullptr, puiWindowX, puiWindowY, puiWidth, puiHeight, puiRefreshRate);
    }
    glfwPollEvents();
    sleep_ms(200);
    CreateWindowSurface(ppVulkanInstance);
    pbRequestRebuild = false;
}

void cWindow::HandleMinimize()
{
    int width = 0, height = 0;
    glfwGetFramebufferSize(poInstance->ppWindow, &width, &height);
    while (width == 0 || height == 0)
    {
        glfwGetFramebufferSize(poInstance->ppWindow, &width, &height);
        glfwWaitEvents();
    }
    RequestRebuild();
}
