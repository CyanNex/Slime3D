#pragma once

#include <pch.hpp>
#include <vulkan/vulkan.h>
#include <vulkan/LogicalDevice.hpp>
#include <vulkan/module/overlay/OverlayRenderModule.hpp>
#include <vulkan/swapchain/SwapChain.hpp>
#include <vulkan/command/CommandBuffer.hpp>

enum eRenderStage
{
    RENDER_STAGE_MRT = 0,
    RENDER_STAGE_LIGHTING = 1,
    RENDER_STAGE_OVERLAY = 2,
};

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
    void SubmitPresentStage(uint uiImageIndex);

    static VkSubmitInfo CreateSubmitInfo(VkSemaphore* poWaitSemaphore, VkPipelineStageFlags eWaitStage,
                                         VkSemaphore* poSignalSemaphore,
                                         VkCommandBuffer* poCommandBuffers, uint uiCommandBufferCount);
};

static VkFence oNullFence = VK_NULL_HANDLE;

cRenderHandler::cRenderHandler(cLogicalDevice* pLogicalDevice,
                               cSwapChain* pSwapChain,
                               cCommandBuffer** pCommandBuffers)
{
    assert(pLogicalDevice != nullptr);
    assert(pSwapChain != nullptr);
    assert(pCommandBuffers != nullptr);

    ppLogicalDevice = pLogicalDevice;
    ppSwapChain = pSwapChain;
    ppCommandBuffers = pCommandBuffers;

    CreateSemaphores();
}

cRenderHandler::~cRenderHandler()
{
    VkDevice& oDevice = ppLogicalDevice->GetDevice();
    for (uint i = 0; i < uiMAX_FRAMES_IN_FLIGHT; i++)
    {
        vkDestroySemaphore(oDevice, aoLightingFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(oDevice, aoMRTFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(oDevice, aoImageAvailableSemaphores[i], nullptr);
        vkDestroyFence(oDevice, aoInFlightFences[i], nullptr);
    }
}

void cRenderHandler::SetUniformHandlers(iUniformHandler** pUniformHandlers, uint uiUniformHandlerCount)
{
    ppUniformHandlers = pUniformHandlers;
    puiUniformHandlerCount = uiUniformHandlerCount;
}

void cRenderHandler::CreateSemaphores()
{
    VkDevice& oDevice = ppLogicalDevice->GetDevice();

    // Resize all the semaphore & fence lists to the max amount of frames in flight
    aoImageAvailableSemaphores.resize(uiMAX_FRAMES_IN_FLIGHT);
    aoMRTFinishedSemaphores.resize(uiMAX_FRAMES_IN_FLIGHT);
    aoLightingFinishedSemaphores.resize(uiMAX_FRAMES_IN_FLIGHT);
    aoInFlightFences.resize(uiMAX_FRAMES_IN_FLIGHT);

    // Struct with information about the semaphores
    VkSemaphoreCreateInfo tSemaphoreInfo = {};
    tSemaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    // Struct with information about the fences
    VkFenceCreateInfo tFenceInfo = {};
    tFenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    tFenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (uint i = 0; i < uiMAX_FRAMES_IN_FLIGHT; i++)
    {
        // For every frame, create the two semaphores and the fence
        if (vkCreateSemaphore(oDevice, &tSemaphoreInfo, nullptr, &aoImageAvailableSemaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(oDevice, &tSemaphoreInfo, nullptr, &aoMRTFinishedSemaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(oDevice, &tSemaphoreInfo, nullptr, &aoLightingFinishedSemaphores[i]) != VK_SUCCESS ||
            vkCreateFence(oDevice, &tFenceInfo, nullptr, &aoInFlightFences[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create semaphores for a frame!");
        }
    }
}

VkSubmitInfo cRenderHandler::CreateSubmitInfo(VkSemaphore* poWaitSemaphore, VkPipelineStageFlags eWaitStage,
                                              VkSemaphore* poSignalSemaphore, VkCommandBuffer* poCommandBuffers,
                                              uint uiCommandBufferCount)
{
    // Struct with information about the command buffer we want to submit to the queue
    VkSubmitInfo tSubmitInfo = {};
    tSubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    // Specifies which semaphores to wait on and in which stage(s) of the pipeline to wait
    VkPipelineStageFlags aeWaitStages[] = {eWaitStage};
    tSubmitInfo.pWaitDstStageMask = aeWaitStages;
    tSubmitInfo.waitSemaphoreCount = 1;
    tSubmitInfo.pWaitSemaphores = poWaitSemaphore;

    // Specify which command buffers to submit
    tSubmitInfo.commandBufferCount = uiCommandBufferCount;
    tSubmitInfo.pCommandBuffers = poCommandBuffers;

    // Specify which semaphores to signal once the command buffer(s) finish
    tSubmitInfo.signalSemaphoreCount = 1;
    tSubmitInfo.pSignalSemaphores = poSignalSemaphore;

    return tSubmitInfo;
}

void cRenderHandler::DrawFrame(cScene* pScene)
{
    // Wait for the fence of the current frame and reset it to the unsignaled state
    ppLogicalDevice->WaitForFences(1, &aoInFlightFences[uiCurrentFrame], VK_TRUE, UINT64_MAX);
    ppLogicalDevice->ResetFences(1, &aoInFlightFences[uiCurrentFrame]);

    // Acquire the next image from the swap chain
    uint uiImageIndex;
    ppSwapChain->AcquireNextImage(UINT64_MAX, aoImageAvailableSemaphores[uiCurrentFrame],
                                  oNullFence, &uiImageIndex);

    if (uiImageIndex == UINT32_MAX) return;

    // If we have a loaded scene, update all the uniform handlers
    if (pScene != nullptr)
    {
        for (uint i = 0; i < puiUniformHandlerCount; i++)
        {
            ppUniformHandlers[i]->UpdateUniformBuffers(pScene);
        }
    }

    this->SubmitMRTRenderStage(uiImageIndex);
    this->SubmitLightingRenderStage(uiImageIndex);
    this->SubmitPresentStage(uiImageIndex);

    // Advance to the next frame
    uiCurrentFrame = (uiCurrentFrame + 1) % uiMAX_FRAMES_IN_FLIGHT;
}

void cRenderHandler::SubmitMRTRenderStage(uint uiImageIndex)
{
    // We want to submit the command buffer for both the MRT stage and the overlay stage
    // because we can let the GPU handle those simultaneously if it wants to.
    VkCommandBuffer aoBuffers[2] = {
            ppCommandBuffers[RENDER_STAGE_MRT]->GetBuffer(uiImageIndex),
            ppCommandBuffers[RENDER_STAGE_OVERLAY]->GetBuffer(uiImageIndex)
    };

    // We need to wait for the image to be available before we can start this stage.
    // Once this stage is done we can signal the MRT finished semaphore.
    VkSubmitInfo tSubmitInfo = CreateSubmitInfo(
            &aoImageAvailableSemaphores[uiCurrentFrame], VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            &aoMRTFinishedSemaphores[uiCurrentFrame],
            aoBuffers, 2
    );

    if (!ppLogicalDevice->GraphicsQueueSubmit(1, &tSubmitInfo, oNullFence))
    {
        throw std::runtime_error("failed to submit draw command buffer!");
    }
}

void cRenderHandler::SubmitLightingRenderStage(uint uiImageIndex)
{
    // We only submit the lighting command buffer for this stage
    VkCommandBuffer oBuffer = ppCommandBuffers[RENDER_STAGE_LIGHTING]->GetBuffer(uiImageIndex);

    // We need to wait for the MRT stage to finish before we can start this stage.
    // Once this stage is done we can signal the lighting finished semaphore.
    VkSubmitInfo tSubmitInfo = CreateSubmitInfo(
            &aoMRTFinishedSemaphores[uiCurrentFrame], VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            &aoLightingFinishedSemaphores[uiCurrentFrame],
            &oBuffer, 1
    );

    if (!ppLogicalDevice->GraphicsQueueSubmit(1, &tSubmitInfo, aoInFlightFences[uiCurrentFrame]))
    {
        throw std::runtime_error("failed to submit draw command buffer!");
    }
}

void cRenderHandler::SubmitPresentStage(uint uiImageIndex)
{
    // Struct with information for submitting the image for presentation
    VkPresentInfoKHR tPresentInfo = {};
    tPresentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    // We need to wait until the lighting stage is finished rendering
    tPresentInfo.waitSemaphoreCount = 1;
    tPresentInfo.pWaitSemaphores = &aoLightingFinishedSemaphores[uiCurrentFrame];

    // Specify the swap chains and the index of the image for each swap chain
    VkSwapchainKHR swapChains[] = {ppSwapChain->poSwapChain};
    tPresentInfo.swapchainCount = 1;
    tPresentInfo.pSwapchains = swapChains;
    tPresentInfo.pImageIndices = &uiImageIndex;

    // Optional, allows you to get a result for every individual swap chain presentation
    tPresentInfo.pResults = nullptr;

    // Queue the image for presentation
    ppLogicalDevice->QueuePresent(&tPresentInfo);
}
