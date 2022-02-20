#pragma once

#include <pch.h>
#include <vulkan/LogicalDevice.h>
#include <vulkan/swapchain/SwapChain.h>
#include <vulkan/command/CommandBuffer.h>
#include <vulkan/uniform/UniformHandler.h>
#include <scene/Scene.h>

class cRenderHandler
{
private:
    const uint uiMAX_FRAMES_IN_FLIGHT = 1;

    cLogicalDevice* ppLogicalDevice = nullptr;
    cSwapChain* ppSwapChain = nullptr;
    cCommandBuffer** ppCommandBuffers = nullptr;
    iUniformHandler** ppUniformHandlers = nullptr;

    uint puiUniformHandlerCount = 0;
    std::vector<VkSemaphore> aoImageAvailableSemaphores;
    std::vector<VkSemaphore> aoMRTFinishedSemaphores;
    std::vector<VkSemaphore> aoLightingFinishedSemaphores;
    std::vector<VkSemaphore> aoComposeFinishedSemaphores;

    std::vector<VkFence> aoInFlightFences;

    uint uiCurrentFrame = 0;

public:
    cRenderHandler(cLogicalDevice* pLogicalDevice,
                   cSwapChain* pSwapChain,
                   cCommandBuffer** pCommandBuffers);
    ~cRenderHandler();

    void CreateSemaphores();

    void DrawFrame(cScene* pScene);

    void SetUniformHandlers(iUniformHandler** pUniformHandlers, uint uiUniformHandlerCount);

private:
    void SubmitMRTRenderStage(uint uiImageIndex);
    void SubmitLightingRenderStage(uint uiImageIndex);
    void SubmitComposeStage(uint uiImageIndex);
    void SubmitPresentStage(uint uiImageIndex);

    static VkSubmitInfo CreateSubmitInfo(VkSemaphore* poWaitSemaphore, VkPipelineStageFlags eWaitStage,
                                         VkSemaphore* poSignalSemaphore,
                                         VkCommandBuffer* poCommandBuffers, uint uiCommandBufferCount);
};
