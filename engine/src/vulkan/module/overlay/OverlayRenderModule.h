#pragma once

#include <pch.h>
#include <vulkan/module/RenderModule.h>
#include <vulkan/command/CommandRecorderProvider.h>
#include <vulkan/module/overlay/element/Font.h>

class cOverlayRenderModule : public cRenderModule, public iCommandRecorderProvider
{
public:
    static cFont* FONT;

private:
    static const uint fontWidth = STB_FONT_arial_50_usascii_BITMAP_WIDTH;
    static const uint fontHeight = STB_FONT_arial_50_usascii_BITMAP_HEIGHT;

    stb_fontchar stbFontData[STB_FONT_arial_50_usascii_NUM_CHARS];
    byte font24pixels[fontHeight][fontWidth];

    cWindow* ppWindow;
//    iGameManager* ppOverlayProvider;

    iCommandBufferRecorder* ppCommandRecorder = nullptr;

public:
    cOverlayRenderModule(cLogicalDevice* pLogicalDevice,
                         cSwapChain* pSwapChain, cWindow* pWindow,
                         std::vector<string>& aShaders/*,
                         iGameManager* pOverlayProvider*/);
    virtual ~cOverlayRenderModule();

    void CreateCommandRecorder();
    iCommandBufferRecorder* GetCommandRecorder() override;

protected:
    void CreateUniformHandler() override;
    void CreateRenderPass() override;
    void CreatePipeline(std::vector<string>& aShaders) override;

private:
    void LoadFont();
};
