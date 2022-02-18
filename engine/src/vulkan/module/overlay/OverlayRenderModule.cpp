#include <vulkan/module/overlay/OverlayRenderModule.h>
#include <vulkan/module/overlay/OverlayUniformHandler.h>
#include <vulkan/module/overlay/OverlayRenderPass.h>
#include <vulkan/module/overlay/OverlayPipeline.h>
#include <vulkan/module/overlay/OverlayRenderRecorder.h>

cFont* cOverlayRenderModule::FONT = nullptr;

cOverlayRenderModule::cOverlayRenderModule(cLogicalDevice* pLogicalDevice,
                                           cSwapChain* pSwapChain, cWindow* pWindow,
                                           std::vector<string>& aShaders/*,
                                           iGameManager* pOverlayProvider*/)
        : cRenderModule(pLogicalDevice, pSwapChain, aShaders)
{
    assert(pWindow != nullptr);
//    assert(pOverlayProvider != nullptr);

    ppWindow = pWindow;
//    ppOverlayProvider = pOverlayProvider;

    LoadFont();
    Init();
}

void cOverlayRenderModule::LoadFont()
{
    stb_font_arial_50_usascii(stbFontData, font24pixels, fontHeight);
    FONT = new cFont(ppLogicalDevice, fontWidth, fontHeight, &font24pixels[0][0], stbFontData);
}

void cOverlayRenderModule::CreateUniformHandler()
{
    ppUniformHandler = new cOverlayUniformHandler(ppLogicalDevice, FONT, ppWindow/*, ppOverlayProvider*/);
}

void cOverlayRenderModule::CreateRenderPass()
{
    ppRenderPass = new cOverlayRenderPass(ppLogicalDevice, ppSwapChain);
}

void cOverlayRenderModule::CreatePipeline(std::vector<string>& aShaders)
{
    ppRenderPipeline = new cOverlayPipeline(ppSwapChain, ppLogicalDevice, ppRenderPass, ppUniformHandler, aShaders);
}

void cOverlayRenderModule::CreateCommandRecorder()
{
    ppCommandRecorder = new cOverlayRenderRecorder(ppRenderPass, ppSwapChain, ppRenderPipeline,
                                                   ppUniformHandler/*, ppOverlayProvider*/);
}

iCommandBufferRecorder* cOverlayRenderModule::GetCommandRecorder()
{
    return ppCommandRecorder;
}

cOverlayRenderModule::~cOverlayRenderModule()
{
    delete FONT;
}
