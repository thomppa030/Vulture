#ifndef VULKAN_DEBUG_MESSENGER_H
#define VULKAN_DEBUG_MESSENGER_H
#include "pch.h"

class VulkanDebugMessenger
{
public:
    VulkanDebugMessenger();
    ~VulkanDebugMessenger();

    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &info);
    void SetupDebugMessenger();

private:

    VkDebugUtilsMessengerEXT m_DebugMessenger;

    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                        VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                        const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                        void *pUserData);

    void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                       VkDebugUtilsMessengerEXT debugMessenger,
                                       const VkAllocationCallbacks *pAllocator);

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                          const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                          const VkAllocationCallbacks *pAllocator,
                                          VkDebugUtilsMessengerEXT *pDebugMessenger);
};

#endif // VULKAN_DEBUG_MESSENGER_H
