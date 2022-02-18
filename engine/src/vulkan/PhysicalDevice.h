#pragma once

#include <pch.h>
#include <optional>
#include <vulkan/vulkan.h>
#include <vulkan/VulkanInstance.h>
#include <vulkan/Window.h>

// A struct for storing the QueueFamily indices
struct tQueueFamilyIndices
{
    std::optional<uint> oulGraphicsFamily;
    std::optional<uint> oulPresentFamily;

    // Return true if the oulGraphicsFamily optional has a value
    bool IsComplete()
    {
        return oulGraphicsFamily.has_value() && oulPresentFamily.has_value();
    }
};

struct tSwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR tCapabilities;
    std::vector<VkSurfaceFormatKHR> atFormats;
    std::vector<VkPresentModeKHR> atPresentModes;
};

class cPhysicalDevice
{
public:
    const std::vector<const char*> DEVICE_EXTENSIONS = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    static bool poSelected;

private:
    static cPhysicalDevice* poInstance;

    cWindow* ppWindow;

    VkPhysicalDevice poPhysicalDevice = VK_NULL_HANDLE;

    VkSampleCountFlagBits puiMaxSampleCount;

public:
    static cPhysicalDevice* GetInstance();

    void SelectPhysicalDevice(cVulkanInstance* pVulkanInstance, cWindow* pWindow);

    tQueueFamilyIndices FindQueueFamilies();
    tSwapChainSupportDetails QuerySwapChainSupport();
    VkSampleCountFlagBits GetMaxSampleCount();
    float GetMaxAnisotropy();

    bool CreateLogicalDevice(VkDeviceCreateInfo* pCreateInfo,
                             VkAllocationCallbacks* pAllocator,
                             VkDevice* pDevice);

    void GetPhysicalMemoryProperties(VkPhysicalDeviceMemoryProperties* pMemoryProperties);
    void GetDeviceFormatProperties(const VkFormat& oFormat,
                                   VkFormatProperties* pFormatProperties);

    void GetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice& oPhysicalDevice,
                                            uint uiQueueFamilyIndex,
                                            cWindow* pWindow,
                                            VkBool32* pSupported);

private:
    cPhysicalDevice();

    bool IsDeviceSuitable(VkPhysicalDevice& oDevice);
    bool CheckDeviceExtensionSupport(VkPhysicalDevice& oDevice);

    tQueueFamilyIndices FindQueueFamilies(VkPhysicalDevice& oDevice);
    tSwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice& oDevice);
    VkSampleCountFlagBits GetMaxSampleCount(VkPhysicalDevice& oDevice);
    float GetMaxAnisotropy(VkPhysicalDevice& oDevice);
};