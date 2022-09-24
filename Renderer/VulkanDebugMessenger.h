#ifndef VULKAN_DEBUG_MESSENGER_H
#define VULKAN_DEBUG_MESSENGER_H
#include "pch.h"
#include "VulkanInstance.h"
#include "VulkanValidation.h"


class VulkanDebugMessenger
{
public:
    VulkanDebugMessenger(VkInstance instance);
    ~VulkanDebugMessenger();

    VkDebugUtilsMessengerEXT GetDebugMessenger() const { return m_debugMessenger; }

private:

    VkInstance m_instance;
    VkDebugUtilsMessengerEXT m_debugMessenger;

    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);

    void SetupDebugMessenger();
    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
};

#endif // VULKAN_DEBUG_MESSENGER_H
