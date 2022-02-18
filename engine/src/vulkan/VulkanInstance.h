#pragma once

#include <pch.h>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

class cVulkanInstance
{
private:
    // List of validation layers we want to enable
    // Validation layers allow you to see warnings and errors from Vulkan
    const std::vector<const char*> pasValidationLayers = {
            "VK_LAYER_KHRONOS_validation"
    };

    // Validation layers should be disabled for production builds
    // as they have a significant performance impact
#ifdef NDEBUG
    const bool pbENABLE_VALIDATION_LAYERS = false;
#else
    const bool pbENABLE_VALIDATION_LAYERS = true;
#endif

    VkInstance poInstance = VK_NULL_HANDLE;

public:
    cVulkanInstance();
    ~cVulkanInstance();

    void EnumeratePhysicalDevices(uint* pPhysicalDeviceCount,
                                  VkPhysicalDevice* pPhysicalDevices);
    bool CreateWindowSurface(GLFWwindow* pWindow,
                             VkAllocationCallbacks* pAllocatorCallback,
                             VkSurfaceKHR* pSurface);
    void DestroyWindowSurface(VkSurfaceKHR& oSurface,
                              VkAllocationCallbacks* pAllocatorCallback);

private:
    bool CheckValidationLayerSupport();
};
