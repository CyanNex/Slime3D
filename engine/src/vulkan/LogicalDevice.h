#pragma once

#include <pch.h>
#include <vulkan/vulkan.h>
#include <vulkan/PhysicalDevice.h>

class cLogicalDevice
{
private:
    // Logical device handle
    VkDevice poDevice = VK_NULL_HANDLE;

    // Supported QueueFamilies
    tQueueFamilyIndices ptQueueIndices;

    // Handle for interfacing with the graphics queue
    VkQueue poGraphicsQueue;

    // Handle for interfacing with the presentation queue
    VkQueue poPresentQueue;

public:
    cLogicalDevice();
    ~cLogicalDevice();

    VkDevice& GetDevice();

    void WaitUntilIdle();

    bool AllocateCommandBuffers(VkCommandBufferAllocateInfo* pAllocateInfo,
                                VkCommandBuffer* pCommandBuffers);
    void FreeCommandBuffers(VkCommandPool& oCommandPool,
                            uint uiCommandBufferCount,
                            VkCommandBuffer* pCommandBuffers);

    bool CreateCommandPool(VkCommandPoolCreateInfo* pCreateInfo,
                           VkAllocationCallbacks* pAllocator,
                           VkCommandPool* pCommandPool);
    void DestroyCommandPool(VkCommandPool& oCommandPool,
                            VkAllocationCallbacks* pAllocator);

    bool CreateShaderModule(VkShaderModuleCreateInfo* pCreateInfo,
                            VkAllocationCallbacks* pAllocator,
                            VkShaderModule* pShaderModule);
    void DestroyShaderModule(VkShaderModule& oShaderModule,
                             VkAllocationCallbacks* pAllocator);

    bool CreatePipelineLayout(VkPipelineLayoutCreateInfo* pCreateInfo,
                              VkAllocationCallbacks* pAllocator,
                              VkPipelineLayout* pPipelineLayout);
    void DestroyPipelineLayout(VkPipelineLayout& oPipelineLayout,
                               VkAllocationCallbacks* pAllocator);

    bool CreateGraphicsPipeline(uint uiCreateInfoCount,
                                VkGraphicsPipelineCreateInfo* pCreateInfos,
                                VkPipeline* pPipelines);
    void DestroyPipeline(VkPipeline& oPipeline,
                         VkAllocationCallbacks* pAllocator);

    bool CreateBuffer(VkBufferCreateInfo* pCreateInfo,
                      VkAllocationCallbacks* pAllocator,
                      VkBuffer* pBuffer);
    void DestroyBuffer(VkBuffer& oBuffer,
                       VkAllocationCallbacks* pAllocator);

    bool AllocateMemory(VkMemoryAllocateInfo* pAllocateInfo,
                        VkAllocationCallbacks* pAllocator,
                        VkDeviceMemory* pMemory);
    void FreeMemory(VkDeviceMemory& oMemory,
                    VkAllocationCallbacks* pAllocator);
    void BindBufferMemory(VkBuffer& oBuffer,
                          VkDeviceMemory& oMemory,
                          VkDeviceSize ulMemoryOffset);

    void MapMemory(VkDeviceMemory& oMemory,
                   VkDeviceSize ulOffset,
                   VkDeviceSize ulSize,
                   VkMemoryMapFlags uiFlags,
                   void** ppData);
    void UnmapMemory(VkDeviceMemory& oDeviceMemory);

    bool GraphicsQueueSubmit(uint uiSubmitCount,
                             VkSubmitInfo* ptSubmitInfo,
                             VkFence& oFence);
    void GraphicsQueueWaitIdle();

    void QueuePresent(VkPresentInfoKHR* ptPresentInfo);

    void WaitForFences(uint uiFenceCount,
                       VkFence* pFences,
                       VkBool32 bWaitAll,
                       uint64 ulTimeout);
    void ResetFences(uint uiFenceCount,
                     VkFence* pFences);

    bool CreateDescriptorSetLayout(VkDescriptorSetLayoutCreateInfo* pCreateInfo,
                                   VkAllocationCallbacks* pAllocator,
                                   VkDescriptorSetLayout* pSetLayout);
    void DestroyDescriptorSetLayout(VkDescriptorSetLayout& oDescriptorSetLayout,
                                    VkAllocationCallbacks* pAllocator);

    bool CreateDescriptorPool(VkDescriptorPoolCreateInfo* pCreateInfo,
                              VkAllocationCallbacks* pAllocator,
                              VkDescriptorPool* pDescriptorPool);
    void DestroyDescriptorPool(VkDescriptorPool& oDescriptorPool,
                               VkAllocationCallbacks* pAllocator);

    bool AllocateDescriptorSets(VkDescriptorSetAllocateInfo* pAllocateInfo,
                                VkDescriptorSet* pDescriptorSets);
    void FreeDescriptorSets(VkDescriptorPool& oDescriptorPool,
                            uint uiDescriptorSetCount,
                            VkDescriptorSet* pDescriptorSets); // TODO: Descriptor sets are never freed?
    void UpdateDescriptorSets(uint uiDescriptorWriteCount,
                              VkWriteDescriptorSet* pDescriptorWrites,
                              uint uiDescriptorCopyCount,
                              VkCopyDescriptorSet* pDescriptorCopies);

    bool CreateImage(VkImageCreateInfo* pCreateInfo,
                     VkAllocationCallbacks* pAllocator,
                     VkImage* pImage);
    void GetImageMemoryRequirements(VkImage& oImage,
                                    VkMemoryRequirements* pMemoryRequirements);
    void BindImageMemory(VkImage& oImage,
                         VkDeviceMemory& oMemory,
                         VkDeviceSize ulMemoryOffset);

    bool CreateImageView(VkImageViewCreateInfo* pCreateInfo,
                         VkAllocationCallbacks* pAllocator,
                         VkImageView* pView);

    bool CreateSampler(VkSamplerCreateInfo* pCreateInfo,
                       VkAllocationCallbacks* pAllocator,
                       VkSampler* pSampler);
    void DestroySampler(VkSampler& oSampler,
                        VkAllocationCallbacks* pAllocator);


private:
    VkDeviceQueueCreateInfo GetQueueCreateInfo(uint uiQueueFamily);
    VkDeviceCreateInfo GetDeviceCreateInfo(std::vector<VkDeviceQueueCreateInfo>& atQueueCreateInfos,
                                           VkPhysicalDeviceFeatures& tDeviceFeatures,
                                           const std::vector<const char*>& apDeviceExtensions);
};
