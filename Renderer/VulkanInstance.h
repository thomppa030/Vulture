#ifndef VULKAN_INSTANCE_H
#define VULKAN_INSTANCE_H
#include "pch.h"


class VulkanInstance {

public:
    VulkanInstance();
    ~VulkanInstance();

    void createInstance();
    VkInstance GetInstance() const { return m_Instance; }


private:

    VkInstance m_Instance;
    VkDebugUtilsMessengerEXT m_DebugMessenger;
    class VulkanDebugMessenger* m_VulkanDebugMessenger;
    class VulkanLogicalDevice* m_VulkanLogicalDevice;
};

#endif // VULKAN_INSTANCE_H