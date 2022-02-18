#pragma once

#include <pch.h>
#include <vulkan/vulkan.h>
#include <vulkan/Window.h>
#include <vulkan/PhysicalDevice.h>
#include <vulkan/LogicalDevice.h>
#include <vulkan/swapchain/SwapChainHelper.h>

struct tOffScreenBuffer
{
    tFrameBufferAttachment ptPositionAttachment;
    tFrameBufferAttachment ptNormalsAttachment;
    tFrameBufferAttachment ptAlbedoAttachment;
    tFrameBufferAttachment ptDepthAttachment;
    tFrameBufferAttachment ptMaterialAttachment;

    VkFramebuffer poFramebuffer;

    VkSampler poSampler; // TODO: This probably doesn't belong here
};

struct tFrameBuffer
{
    tFrameBufferAttachment ptColorAttachment;

    VkFramebuffer poFramebuffer;
};

class cSwapChain
{
private:
    cLogicalDevice* ppLogicalDevice;
    cWindow* ppWindow;

    std::vector<VkImage> paoSwapChainImages;
    std::vector<VkImageView> paoSwapChainImageViews;
    std::vector<VkFramebuffer> paoSwapChainFramebuffers;

    tOffScreenBuffer ptOffScreenBuffer;
    tFrameBuffer ptOverlayBuffer;

public:
    VkSwapchainKHR poSwapChain; // TODO: Remove public access

    VkExtent2D ptSwapChainExtent;
    VkFormat peSwapChainImageFormat;

    static VkSampleCountFlagBits peSampleCount;

    cSwapChain(cLogicalDevice* pLogicalDevice,
               cWindow* pWindow);
    ~cSwapChain();

    void CreateFramebuffers(VkRenderPass& oFinalRenderPass,
                            VkRenderPass& oOffScreenRenderPass,
                            VkRenderPass& oOverlayRenderPass);
    void CreateResources();

    uint GetFramebufferSize();
    VkFramebuffer& GetFramebuffer(uint index);
    tFrameBufferAttachment& GetAttachment(uint uiIndex);
    VkSampler& GetSampler();
    VkFramebuffer& GetOffScreenFramebuffer();
    tFrameBufferAttachment& GetOverlayAttachment();
    VkFramebuffer& GetOverlayFramebuffer();

    void AcquireNextImage(int64 ulTimeout,
                          VkSemaphore& oSemaphore,
                          VkFence& oFence,
                          uint* puiImageIndex);

    void RebuildSwapChain();

private:
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& atAvailableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& atAvailablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& tCapabilities, cWindow* pWindow);
    uint ChooseSwapImageCount(const VkSurfaceCapabilitiesKHR& tCapabilities);

    VkSwapchainCreateInfoKHR GetSwapChainCreateInfo(VkSurfaceFormatKHR& tSurfaceFormat,
                                                    VkPresentModeKHR ePresentMode,
                                                    VkExtent2D& tExtent,
                                                    uint uiImageCount,
                                                    cWindow* pWindow,
                                                    cPhysicalDevice* pPhysicalDevice,
                                                    tSwapChainSupportDetails& tSwapChainSupport);

    void CreateSwapChain(cWindow* pWindow);
    void CreateImageViews();

    void Cleanup();
};
