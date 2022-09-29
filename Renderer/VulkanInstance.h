#ifndef VULKAN_INSTANCE_H
#define VULKAN_INSTANCE_H
#include "pch.h"


class VulkanInstance
{

public:
    VulkanInstance(GLFWwindow *window);
    ~VulkanInstance();

    void createInstance();
    static VkInstance GetInstance()
    {
        return m_Instance;
    }

private:
    GLFWwindow *m_Window;

    VkDebugUtilsMessengerEXT m_DebugMessenger;

    class VulkanDebugMessenger *m_VulkanDebugMessenger;
    class VulkanSurface *m_VulkanSurface;
    class VulkanSwapchain *m_VulkanSwapchain;
    class VulkanPhysicalDevice *m_VulkanPhysicalDevice;
    class VulkanLogicalDevice *m_VulkanLogicalDevice;
    class VulkanGraphicsPipeline *m_VulkanGraphicsPipeline;

    inline static VkInstance m_Instance;
};

#endif // VULKAN_INSTANCE_H