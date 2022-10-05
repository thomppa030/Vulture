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

    void drawFrame();

private:
    GLFWwindow *m_Window;

    VkDebugUtilsMessengerEXT m_DebugMessenger;

    class VulkanDebugMessenger *m_VulkanDebugMessenger;
    class VulkanSurface *m_VulkanSurface;
    class VulkanSwapchain *m_VulkanSwapchain;
    class VulkanRenderPass *m_VulkanRenderPass;
    class VulkanPhysicalDevice *m_VulkanPhysicalDevice;
    class VulkanLogicalDevice *m_VulkanLogicalDevice;
    class VulkanGraphicsPipeline *m_VulkanGraphicsPipeline;
    class VulkanVertexBuffer *m_VulkanVertexBuffer;

    VkCommandPool m_CommandPool;
    std::vector<VkCommandBuffer> m_CommandBuffers;

    std::vector<VkSemaphore> m_ImageAvailableSemaphores;
    std::vector<VkSemaphore> m_RenderFinishedSemaphores;
    std::vector<VkFence> m_InFlightFences;


    void createCommandPool();
    void createCommandBuffer();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void createSyncObjects();

    uint32_t m_CurrentFrame{0};

    inline static VkInstance m_Instance;
};

#endif // VULKAN_INSTANCE_H